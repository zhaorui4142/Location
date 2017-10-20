#define NUM_GAUSS 10

varying vec2 textureCoord;
uniform sampler2D tex;
uniform int radius;//ģ���뾶,����
uniform int pixelWidth;//���ڿ�ȣ�����


float getGaussNum(float x)
{
    float pi = 3.1415927f;
    float e = 2.71828f;
    float theta = 1.0f;//����1ʱΪ��׼��̬�ֲ�
    float theta2 = theta * theta;
    float temp1 = 1.0f / (theta * sqrt(2 * pi));
    float temp2 = pow(e, -(x * x) / 2 * theta2);
    return temp1 * temp2;
}

void main()
{
    //��˹�����㵽+-3.0
    float gauss_step = 3.0/radius;
    float coord_step = 1.0/pixelWidth;
    float color = 0.0;
    for(int i=-radius; i<=radius; i++)
    {
        float tex_color = texture2D(tex, vec2(textureCoord.x + i * coord_step, textureCoord.y)).r;//��������ɫ
        float weight = getGaussNum(i * gauss_step);//ռ��Ȩ��
        color += (tex_color * weight);//�ۼ�
    }
    gl_FragColor = vec4(color, color, color, 1.0);
}
