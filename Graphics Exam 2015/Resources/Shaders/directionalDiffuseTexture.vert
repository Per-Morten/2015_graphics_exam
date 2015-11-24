#version 410

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 textureCoordinate;

uniform vec3 VertexColor;
uniform mat4 MVP;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

out vec4 fragmentColor;
out vec2 fragmentTextureCoordinate;
out vec3 fragmentNormal;

void main()
{
	gl_Position = MVP * vec4(vertexPosition, 1.0);
	fragmentColor = vec4(VertexColor, 1.0);
	fragmentTextureCoordinate = textureCoordinate;
	fragmentNormal = vertexNormal;
}