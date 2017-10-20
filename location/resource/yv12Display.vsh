/*attribute highp vec4 qt_Vertex;
attribute highp vec4 qt_MultiTexCoord0;
uniform highp mat4 qt_ModelViewProjectionMatrix;
varying highp vec4 qt_TexCoord0;

void main(void)
{
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    qt_TexCoord0 = qt_MultiTexCoord0;
}*/

attribute vec4 vertexIn;
attribute vec2 textureIn;
varying vec2 textureCoord;
void main(void)
{
    gl_Position = vertexIn;
    textureCoord = textureIn;
}
