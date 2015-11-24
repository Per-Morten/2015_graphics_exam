#version 410

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 textureCoordinate;

uniform vec4 VertexColor;
uniform mat4 MVP;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

out vec4 fragmentColor;
out vec2 fragmentTextureCoordinate;
out vec3 fragmentNormal;
out vec4 fragmentPosition_worldSpace;

void main()
{
	gl_Position = MVP * vec4(vertexPosition, 1.0);
	fragmentColor = VertexColor;
	fragmentTextureCoordinate = textureCoordinate;

	// Matrix magic that removes scale and translation on the normals
	// From the model matrix,
	// We are still interested in rotation
	// Could be optimized by being set in the source code, 
	// doing it per vertex is a lot of repeated calculations
	mat3 normalMatrix = transpose(inverse(mat3(ModelMatrix)));
	
	// Apply the normalMatrix to the normals
	fragmentNormal = normalize(normalMatrix * vertexNormal);

	// Apply the model matrix to transform the fragmentPosition
	fragmentPosition_worldSpace = ModelMatrix * vec4(vertexPosition, 1.0);
}