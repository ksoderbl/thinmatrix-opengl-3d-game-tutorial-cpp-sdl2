#version 140

in vec2 pass_textureCoordinates;
in vec3 surfaceNormal;
// The shaders use 4 light sources. If this is changed, change also the
// MAX_LIGHTS constant in StaticShader.h.
in vec3 toLightVector[4];
in vec3 toCameraVector;
in float visibility;

out vec4 out_Color;

uniform sampler2D modelTexture;
uniform vec3 lightColor[4];
uniform vec3 attenuation[4];
uniform float shineDamper;
uniform float reflectivity;
uniform vec3 skyColor;

// cel shading
//const float levels = 4.0; // tutorial 30 cel shading

void main() {
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitVectorToCamera = normalize(toCameraVector);

	vec3 totalDiffuse = vec3(0.0);
	vec3 totalSpecular = vec3(0.0);

	for (int i = 0; i < 4; i++) {
		float distance = length(toLightVector[i]);
		float attFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);
		vec3 unitLightVector = normalize(toLightVector[i]);
		float nDot1 = dot(unitNormal, unitLightVector);
		float brightness = max(nDot1, 0.0);

		// cel shading
		//float level = floor(brightness * levels);
		//brightness = level / levels;

		vec3 lightDirection = -unitLightVector;
		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
		specularFactor = max(specularFactor, 0.0);
		float dampedFactor = pow(specularFactor, shineDamper);

		// cel shading
		//level = floor(dampedFactor * levels);
		//dampedFactor = level / levels;

		totalDiffuse = totalDiffuse + (brightness * lightColor[i]) / attFactor;
		totalSpecular = totalSpecular + (dampedFactor * reflectivity * lightColor[i]) / attFactor;
	}
	// 0.2 = ambient light
	totalDiffuse = max(totalDiffuse, 0.2);

	vec4 textureColor = texture(modelTexture, pass_textureCoordinates);
	if (textureColor.a < 0.5) {
		discard;
	}

	out_Color = vec4(totalDiffuse,1.0) * textureColor + vec4(totalSpecular, 1.0);
	out_Color = mix(vec4(skyColor, 1.0), out_Color, visibility);
}
