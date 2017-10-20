
attribute vec4 vertexIn;
attribute vec2 textureIn;
varying vec2 texCoord;
void main(void)
{
    gl_Position = vertexIn;
    texCoord = textureIn;
}
