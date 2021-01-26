#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 matModelViewProjection;

void main()
{
	gl_Position = matModelViewProjection * vec4(aPos, 1.f);
}