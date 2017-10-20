
varying vec2 texCoord;
uniform float scanline_x;//scanline_x:(0.0 +3.0)
uniform sampler2D tex_y;
uniform sampler2D tex_u;
uniform sampler2D tex_v;
uniform sampler2D tex_edge;


void main(void)
{
    //yuv转rgb
    vec3 yuv = vec3(texture2D(tex_y, texCoord).r - 0.0625,
                    texture2D(tex_u, texCoord).r - 0.5,
                    texture2D(tex_v, texCoord).r - 0.5);

    vec3 img_color = mat3(1.164383,   1.164383,   1.164383,
                          0,          -0.391762,  2.017232,
                          1.596027,   -0.812968,  0         ) * yuv;

    //绘制扫描线扫过的区域
    if(texCoord.x < scanline_x)
    {
        //背景图像先变暗
        float ratio = min((3.0-scanline_x)/2, 0.5);
        img_color = mix(img_color, vec3(0.0,0.0,0.0), ratio);

        //绘制网格线
        vec3  line_color = vec3(0.679, 0.812, 0.765);//叠加到图像上的颜色
        float line_coord = min((scanline_x - texCoord.x), 1.0);//根据扫描线的位置计算坐标偏移
        ratio = pow(line_coord, 0.05);//网格背景的融合系数
        if (mod(gl_FragCoord.x, 5) == 0.5)      ratio = pow(line_coord, 0.5);//网格线上的融合系数
        if (mod(gl_FragCoord.y, 5) == 0.5)      ratio = pow(line_coord, 0.5);
        img_color = mix(line_color, img_color, ratio);

        //绘制边缘轮廓
        line_coord = scanline_x - texCoord.x;
        if(line_coord > 2.0) line_coord = 0.0;
        if(line_coord > 1.0) line_coord = 2.0 - line_coord;
        ratio = texture2D(tex_edge, texCoord).r * pow(line_coord, 0.7);
        img_color = mix(img_color, line_color, ratio);
    }

    gl_FragColor = vec4(img_color, 1.0);
    //gl_FragColor = vec4(texture2D(tex_edge, texCoord).rgb,1.0);
}







//计算坐标，准备绘制网格

//float line_coord = clamp((1.0 - texCoord.x + scanline_x), 0.0,1.0);//根据扫描线的位置计算坐标偏移

//float mix_ratio_grid = pow(line_coord, 0.5 );//网格线上的融合系数
//float mix_ratio_back = pow(line_coord, 0.05);//网格背景的融合系数


//float ratio2 = clamp(sin(1.5708*scanline_x), 0.0, 1.0);

//vec3 pixel;
//vec3 edge = texture2D(tex_edge, texCoord).rrr;
//if(texCoord.x < scanline_x + 1.0)
//{
    //pixel = mix(img_color, edge, ratio2);
    //gl_FragColor = vec4(mix(line_color, pixel, ratio1),1.0);
//}


//ratio = texture2D(tex_edge, texCoord).r * 0.3;
//if(scanline_x > 1.0)
//{
    //line_coord = min((scanline_x - texCoord.x), 1.0);
    //ratio = ratio + (((1-0.3)/0.3) * ratio * pow((scanline_x - 1.0), 1.8));
//}
//if(scanline_x > 2.0)
//{
    //ratio = 0.0;
    //ratio = ratio * pow(abs(3.0-scanline_x), 1.5);
//}





