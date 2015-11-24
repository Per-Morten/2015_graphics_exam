#version 410 

in vec4 fragmentColor;
in vec2 fragmentTextureCoordinate;
in vec3 fragmentNormal;
in vec4 fragmentPosition_worldSpace;

out vec4 finalColor;

uniform sampler2D TextureBuffer;
uniform float AmbientFactor;
uniform vec3 DirectionalLightDirection;
uniform vec3 CameraPosition_worldSpace;

vec4 calculateDiffuseColor(vec4 materialColor, 
						   vec3 normal, 
						   vec3 lightDirection, 
						   vec4 lightColor)
{
	// cosine of the angle between the normal and the light direction
	// clamp above 0.
	// Light is at the vertical of the triangle -> 1
	// Light is perpendicular to the triangle -> 0
	// Light is behind the triangle -> 0
	// basically, the smaller angle between the lightDirection and normal, the more its lit up, as cosine of angle gets larger.
	float normalLightDotProduct = dot(normal, lightDirection);
	normalLightDotProduct = clamp(normalLightDotProduct, 0, 1);

	// Diffuse color depends on the color of the light,
	// normal lightdirection dot product,
	// and the material color.
	vec4 diffuseColor = lightColor * normalLightDotProduct * materialColor;
	return diffuseColor;
}

vec4 calculateSpecularColor(vec4 materialSpecularColor,
							vec3 normal,
							vec3 lightDirection,
							float specularExponent,
							vec4 lightColor)
{
	// Calculate vector towards camera
	// Basically camera's look at direction reversed
	vec4 eyeDirection = vec4(CameraPosition_worldSpace, 1.0) - fragmentPosition_worldSpace;
	eyeDirection = normalize(eyeDirection);

	vec3 lightReflectionDirection = reflect(-lightDirection, normal);

	// How much light goes directly off the floor, ie everything with a "stiff" angle
	float normalLightDotProduct = dot(normal, lightDirection);
	normalLightDotProduct = ceil(clamp(normalLightDotProduct, 0.0, 1.0));

	// How much of that reflects into your eyes/camera.								// 0 cause vector
	float eyeReflectionDotProduct = dot(eyeDirection, vec4(lightReflectionDirection, 0.0));
	eyeReflectionDotProduct = clamp(eyeReflectionDotProduct, 0.0, 1.0);

	vec4 specularColor = lightColor * pow(eyeReflectionDotProduct, specularExponent) * materialSpecularColor * normalLightDotProduct;

	return specularColor;
}

void main()
{
	//**********
	//* COLORS *
	//**********
	vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);

	vec4 textureColor = texture(TextureBuffer, fragmentTextureCoordinate.xy);
	
	// Material Color
	vec4 materialColor = fragmentColor * textureColor;
	
	// Ambient color
	vec4 materialAmbientColor = materialColor * AmbientFactor;
	
	// Diffuse uses material color

	// Specular Color
	vec4 materialSpecularColor = vec4(1.0, 1.0, 1.0, 1.0);
	float specularExponent = 100.0;
	
	//********
	//* MATH *
	//********
	// Normalize the normals, and light direction so math does not crash
	vec3 normalizedNormal = normalize(fragmentNormal);
	vec3 normalizedLightDirection = normalize(DirectionalLightDirection);
	
	// Calculate diffuse
	vec4 lightDiffuseStrenght = calculateDiffuseColor(materialColor, normalizedNormal, normalizedLightDirection, lightColor);
	
	vec4 specularLightStrength = calculateSpecularColor(materialSpecularColor, normalizedNormal, normalizedLightDirection, specularExponent, lightColor);

	finalColor = materialAmbientColor + lightDiffuseStrenght + specularLightStrength;
}