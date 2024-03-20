#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

uniform mat4 matrix;
out vec4 pos;

out vec3 vertexNormal;
out vec3 fragmentPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * position;
	fragmentPosition = vec3(model * position);
	vertexNormal = mat3(transpose(inverse(model))) * normal;

}

