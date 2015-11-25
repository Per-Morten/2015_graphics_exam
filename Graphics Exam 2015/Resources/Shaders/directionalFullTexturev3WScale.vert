#version 410 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;
layout(location = 2) in vec2 textureCoordinate;

out vec2 fragmentTextureCoordinate;
out vec4 fragmentColor;
out vec3 fragmentPosition_cameraspace;
out vec3 fragmentNormal_cameraspace;
out vec3 lightDirection_cameraspace;

uniform vec4 VertexColor;
uniform mat4 MVP;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;
uniform vec3 LightDirection_worldspace;
uniform mat4 WorldScale;
uniform mat4 ProjectionMatrix;

void main()
{
	vec4 vertexPosition = vec4(vertexPosition_modelspace,1.0);	
	
	mat4 MVPS = ProjectionMatrix * ViewMatrix * WorldScale * ModelMatrix;
	
	gl_Position = MVPS * vertexPosition;

	fragmentTextureCoordinate = textureCoordinate;

	fragmentColor = VertexColor;

	fragmentPosition_cameraspace = vec3(ViewMatrix * ModelMatrix * vec4(vertexPosition_modelspace, 1.0));

	fragmentNormal_cameraspace = normalize(NormalMatrix * vertexNormal_modelspace);

	lightDirection_cameraspace = normalize(vec3(ViewMatrix * vec4(LightDirection_worldspace, 0.0)));
}
