
attribute vec4  vertexIn;
attribute vec4  textureIn;
varying vec4    textureCoord;

void main(void)
{
    gl_Position = vertexIn;
    textureCoord = textureIn;
}

