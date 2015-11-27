#version 410 core

in vec2 fragmentTextureCoordinate;
in vec4 fragmentColor;
in vec3 fragmentPosition_cameraspace;
in vec3 fragmentNormal_cameraspace;
in vec3 lightDirection_cameraspace;

uniform sampler2D textureBuffer;
uniform float AmbientFactor;


out vec4 finalColor;

vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);


vec4 calculateDiffuseColor(vec4 materialDiffuseColor, vec3 normal, vec3 lightDirection)
{
		// cosine of the angle between the normal and the lgiht direction, camped above 0
	// *light is at the vertical of the triangle -> 1
	// *light is perpendicular to the triangle -> 0
	// *light is behind the triangle -> 0
	float normalLightDotProduct = dot(normal, lightDirection);
	normalLightDotProduct = clamp(normalLightDotProduct, 0.0, 1.0);

	// The diffuse color depends on the color of the light,
	// the normal light direction dot product
	// and color of the material
	vec4 diffuseColor = lightColor * normalLightDotProduct * materialDiffuseColor;

	return diffuseColor;
}

vec4 calculateSpecularColor(vec4 materialSpecularColor, vec3 normal, vec3 lightDirection, float specularExponent)
{
		//eye vector (towards camera)
	vec4 eyeDirection = vec4(0.0f, 0.0f, 0.0, 1.0) - vec4(fragmentPosition_cameraspace, 1.0);
	eyeDirection = normalize(eyeDirection);


	vec3 lightReflectionDirection = reflect(-lightDirection, normal);

	float normalLightDotProduct = dot(normal, lightDirection);
	normalLightDotProduct = ceil(clamp(normalLightDotProduct, 0.0, 1.0));

	float eyeReflectionDotProduct = dot(eyeDirection, vec4(lightReflectionDirection, 0.0));
	eyeReflectionDotProduct = clamp(eyeReflectionDotProduct, 0.0, 1.0);

	vec4 specularColor = lightColor * pow(eyeReflectionDotProduct, specularExponent) * materialSpecularColor * normalLightDotProduct;

	return specularColor;
}

void main()
{
	vec4 textureColor = texture(textureBuffer, fragmentTextureCoordinate);

	vec4 coloredTexture = textureColor * fragmentColor;

	vec4 materialDiffuseColor = coloredTexture;
	vec4 materialAmbientColor = materialDiffuseColor * AmbientFactor;

	//specular
	vec4 materialSpecularColor = vec4(1.0, 1.0, 1.0, 1.0);
	float specularExponent = 200;


	vec4 diffuseColor = calculateDiffuseColor(materialDiffuseColor, fragmentNormal_cameraspace, lightDirection_cameraspace);
	vec4 specularColor = calculateSpecularColor(materialSpecularColor, fragmentNormal_cameraspace, lightDirection_cameraspace, specularExponent);

	finalColor = materialAmbientColor + diffuseColor + specularColor;

}