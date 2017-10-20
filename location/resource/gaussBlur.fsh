varying vec2 textureCoord;
uniform sampler2D tex;
uniform vec2 texSize;

void main()
{
    //获得当前片元的XY坐标
    vec2 intXY = vec2(textureCoord.x * texSize.x, textureCoord.y * texSize.y);

    //高斯内核
    mat3 _smooth_fil         = mat3(1.0/16.0, 2.0/16.0, 1.0/16.0,
                                    2.0/16.0, 4.0/16.0, 2.0/16.0,
                                    1.0/16.0, 2.0/16.0, 1.0/16.0);

    mat3 _filter_pos_delta_x = mat3(vec3(-1.0, 0.0, 1.0),
                                    vec3(0.0, 0.0, 1.0),
                                    vec3( 1.0, 0.0, 1.0));

    mat3 _filter_pos_delta_y = mat3(vec3(-1.0,-1.0,-1.0),
                                    vec3(-1.0,0.0, 0.0),
                                    vec3(-1.0, 1.0, 1.0));

    vec4 final_color = vec4(0.0, 0.0, 0.0, 0.0);

    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            vec2 _xy_new = vec2(intXY.x + _filter_pos_delta_x[i][j], intXY.y + _filter_pos_delta_y[i][j]);
            vec2 _uv_new = vec2(_xy_new.x/texSize.x, _xy_new.y/texSize.y);
            final_color += texture2D(tex,_uv_new) * _smooth_fil[i][j];
        }
    }

    gl_FragColor = final_color;
};


//网上找的高斯模糊模板
/*precision mediump float;
vec4 dip_filter(mat3 _filter, sampler2D _image, vec2 _xy, vec2 texSize)
{
    mat3 _filter_pos_delta_x=mat3(vec3(-1.0, 0.0, 1.0), vec3(0.0, 0.0, 1.0), vec3( 1.0, 0.0, 1.0));
    mat3 _filter_pos_delta_y=mat3(vec3(-1.0,-1.0,-1.0), vec3(-1.0,0.0, 0.0), vec3(-1.0, 1.0, 1.0));
    vec4 final_color = vec4(0.0, 0.0, 0.0, 0.0);
    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            vec2 _xy_new = vec2(_xy.x + _filter_pos_delta_x[i][j], _xy.y + _filter_pos_delta_y[i][j]);
            vec2 _uv_new = vec2(_xy_new.x/texSize.x, _xy_new.y/texSize.y);
            final_color += texture2D(_image,_uv_new) * _filter[i][j];
        }
    }
    return final_color;
}
varying vec2 v_texCoord;
uniform vec2 TexSize;
uniform sampler2D s_baseMap;
void main()
{
    vec2 intXY = vec2(v_texCoord.x * TexSize.x, v_texCoord.y * TexSize.y);
    mat3 _smooth_fil = mat3(1.0/16.0, 2.0/16.0, 1.0/16.0,
                            2.0/16.0, 4.0/16.0, 2.0/16.0,
                            1.0/16.0, 2.0/16.0, 1.0/16.0);
    vec4 tmp = dip_filter(_smooth_fil, s_baseMap, intXY, TexSize);
    gl_FragColor = tmp;
};*/
