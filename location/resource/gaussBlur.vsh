
attribute vec4 vertexIn;
attribute vec2 textureIn;
varying vec2 textureCoord;

void main(void)
{
    gl_Position = vertexIn;
    textureCoord = textureIn;
}


