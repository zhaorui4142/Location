
uniform sampler2D   texture;
varying vec4        textureCoord;

void main(void)
{
    gl_FragColor = texture2D(texture, textureCoord.st);
}
