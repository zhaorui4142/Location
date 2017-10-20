#define NUM_GAUSS 10

varying vec2 textureCoord;
uniform sampler2D tex;
uniform int radius;//模糊半径,像素
uniform int pixelWidth;//窗口宽度，像素


float getGaussNum(float x)
{
    float pi = 3.1415927f;
    float e = 2.71828f;
    float theta = 1.0f;//等于1时为标准正态分布
    float theta2 = theta * theta;
    float temp1 = 1.0f / (theta * sqrt(2 * pi));
    float temp2 = pow(e, -(x * x) / 2 * theta2);
    return temp1 * temp2;
}

void main()
{
    //高斯数计算到+-3.0
    float gauss_step = 3.0/radius;
    float coord_step = 1.0/pixelWidth;
    float color = 0.0;
    for(int i=-radius; i<=radius; i++)
    {
        float tex_color = texture2D(tex, vec2(textureCoord.x + i * coord_step, textureCoord.y)).r;//附近的颜色
        float weight = getGaussNum(i * gauss_step);//占的权重
        color += (tex_color * weight);//累加
    }
    gl_FragColor = vec4(color, color, color, 1.0);
}
