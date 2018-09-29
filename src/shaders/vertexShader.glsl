#version 140

in vec3 position;
in vec2 textureCoordinates;
in vec3 normal;

out vec2 pass_textureCoordinates;
out vec3 surfaceNormal;
out vec3 toLightVector[4];
out vec3 toCameraVector;
out float visibility;

uniform mat4 transformationMatrix; // objects translation, rotation and scaling in the world cooridinates
uniform mat4 projectionMatrix;     // frustum
uniform mat4 viewMatrix;           // camera
uniform vec3 lightPosition[4];

uniform float useFakeLighting;

uniform float numberOfRows;
uniform vec2 textureOffset;

const float fogDensity = 0.00155;
const float fogGradient = 2.0;

uniform vec4 clipPlane;

void main() {
	// local space -> world space
	vec4 worldPosition = transformationMatrix * vec4(position, 1.0);

	gl_ClipDistance[0] = dot(worldPosition, clipPlane);

	// world space -> eye space
	vec4 positionRelativeToCam = viewMatrix * worldPosition;

	// eye space -> homogenous clip space
	gl_Position = projectionMatrix * positionRelativeToCam;
	pass_textureCoordinates = (textureCoordinates/numberOfRows) + textureOffset;
	
	vec3 actualNormal = normal;
	if (useFakeLighting > 0.5) {
		actualNormal = vec3(0.0, 1.0, 0.0);
	}

	surfaceNormal = (transformationMatrix * vec4(actualNormal,0.0)).xyz;
	for (int i = 0; i < 4; i++) {
		toLightVector[i] = lightPosition[i] - worldPosition.xyz;
	}
	toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;

	float distance = length(positionRelativeToCam.xyz);
	visibility = exp(-pow((distance * fogDensity), fogGradient));
	visibility = clamp(visibility, 0.0, 1.0);
}
