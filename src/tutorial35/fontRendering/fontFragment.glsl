#version 140

in vec2 pass_textureCoords;

out vec4 out_color;

uniform vec3 color;
uniform sampler2D fontAtlas;

const float width = 0.45;
const float edge = 0.1;

const float borderWidth = 0.7;
const float borderEdge = 0.1;

const vec2 offset = vec2(0.001, 0.001);

const vec3 outlineColor = vec3(0.0, 0.0, 0.0);

void main(void)
{
	float distance = 1.0 - texture(fontAtlas, pass_textureCoords).a;
	float alpha = 1.0 - smoothstep(width, width + edge, distance);
	
	float distance2 = 1.0 - texture(fontAtlas, pass_textureCoords + offset).a;
	float outlineAlpha = 1.0 - smoothstep(borderWidth, borderWidth + borderEdge, distance2);
	
	//float overallAlpha = alpha + (1.0 - alpha) * outlineAlpha;
	float overallAlpha = 1.0; 
	vec3 overallColor = mix(outlineColor, color, alpha / overallAlpha);
	
	//out_color = vec4(color, texture(fontAtlas, pass_textureCoords).a);
	out_color = vec4(overallColor, outlineAlpha);
}
