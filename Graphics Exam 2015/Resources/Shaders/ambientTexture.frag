#version 410 

in vec4 fragmentColor;
in vec2 fragmentTextureCoordinate;

out vec4 finalColor;

uniform sampler2D TextureBuffer;
uniform float AmbientFactor;

void main()
{
	vec4 textureColor = texture(TextureBuffer, fragmentTextureCoordinate.xy);
	
	finalColor = fragmentColor * textureColor * AmbientFactor;
}