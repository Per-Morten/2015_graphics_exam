#version 410 

in vec4 fragmentColor;
in vec2 fragmentTextureCoordinate;
in vec3 fragmentNormal;

out vec4 finalColor;

uniform sampler2D TextureBuffer;
uniform float AmbientFactor;
uniform vec3 DirectionalLightDirection;

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

void main()
{
	vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);

	vec4 textureColor = texture(TextureBuffer, fragmentTextureCoordinate.xy);
	
	vec4 materialColor = fragmentColor * textureColor;
	vec4 materialAmbientColor = materialColor * AmbientFactor;

	vec3 normalizedNormal = normalize(fragmentNormal);
	vec3 normalizedLightDirection = normalize(DirectionalLightDirection);
	
	vec4 lightDiffuseStrenght = calculateDiffuseColor(materialColor, normalizedNormal, normalizedLightDirection, lightColor);
	
	finalColor = materialAmbientColor + lightDiffuseStrenght;
}