#version 140

in vec2 position;

out vec4 clipSpace;
out vec2 textureCoords;
out vec3 toCameraVector;
out vec3 fromLightVector;
out float visibility;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

uniform vec3 cameraPosition;

uniform float waterTiling;

uniform float fogDensity;
uniform float fogGradient;

void main(void) {
	// local space -> world space
	vec4 worldPosition = transformationMatrix * vec4(position.x, 0.0, position.y, 1.0);

	// world space -> eye space
	vec4 positionRelativeToCam = viewMatrix * worldPosition;

	clipSpace = projectionMatrix * viewMatrix * worldPosition;
	gl_Position = clipSpace;
	textureCoords = vec2(position.x / 2.0 + 0.5, position.y / 2.0 + 0.5) * waterTiling;
	toCameraVector = cameraPosition - worldPosition.xyz;
	fromLightVector = worldPosition.xyz - lightPosition;

	float distance = length(positionRelativeToCam.xyz);
	visibility = exp(-pow((distance * fogDensity), fogGradient));
	visibility = clamp(visibility, 0.0, 1.0);
}
