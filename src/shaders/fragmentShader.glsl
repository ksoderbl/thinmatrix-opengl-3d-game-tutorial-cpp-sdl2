#version 150 core

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;

out vec4 out_color;

uniform sampler2D textureSampler;
// Tutorial 11
uniform vec3 lightColor;
// Tutorial 12
uniform float shineDamper;
uniform float reflectivity;

void main() {
  vec3 unitNormal = normalize(surfaceNormal);
  vec3 unitLightVector = normalize(toLightVector);
  
  float nDot1 = dot(unitNormal, unitLightVector);
  float brightness = max(nDot1, 0.2); // 0.2 = ambient light
  vec3 diffuse = brightness * lightColor;

  vec3 unitVectorToCamera = normalize(toCameraVector);
  vec3 lightDirection = -unitLightVector;
  vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

  float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
  specularFactor = max(specularFactor, 0.0);
  float dampedFactor = pow(specularFactor, shineDamper);
  vec3 finalSpecular = dampedFactor * reflectivity * lightColor;

  vec4 textureColor = texture(textureSampler, pass_textureCoords);
  if (textureColor.a < 0.5) {
	  discard;
  }
  
  out_color = vec4(diffuse,1.0) * textureColor + vec4(finalSpecular, 1.0);
}
