
varying vec2 textureCoord;
uniform sampler2D tex_y;
uniform sampler2D tex_u;
uniform sampler2D tex_v;
void main(void)
{
    vec3 yuv;
    vec3 rgb;


    //公式1
    /*
    yuv.x = texture2D(tex_y, textureCoord).r;
    yuv.y = texture2D(tex_u, textureCoord).r - 0.5;
    yuv.z = texture2D(tex_v, textureCoord).r - 0.5;
    rgb = mat3( 1,       1,         1,
                0,       -0.39465,  2.03211,
                1.13983, -0.58060,  0) * yuv;
    //公式2
    yuv.x = texture2D(tex_y, textureCoord).r;
    yuv.y = texture2D(tex_u, textureCoord).r - 0.5;
    yuv.z = texture2D(tex_v, textureCoord).r - 0.5;
    rgb = mat3( 1,       1,         1,
                0,       -0.34413,  1.772,
                1.402,   -0.71414,  0) * yuv;*/
    //公式3
    yuv.x = texture2D(tex_y, textureCoord).r - 0.0625;
    yuv.y = texture2D(tex_u, textureCoord).r - 0.5;
    yuv.z = texture2D(tex_v, textureCoord).r - 0.5;
    rgb = mat3( 1.164383,     1.164383,    1.164383,
                0,           -0.391762,    2.017232,
                1.596027,    -0.812968,           0) * yuv;

    gl_FragColor = vec4(rgb, 1);
}
