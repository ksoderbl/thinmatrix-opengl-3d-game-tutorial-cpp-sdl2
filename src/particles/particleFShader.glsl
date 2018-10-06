#version 140

in vec2 textureCoords;

out vec4 out_color;

uniform sampler2D particleTexture;

void main(void)
{
	out_color = texture(particleTexture, textureCoords);
}
