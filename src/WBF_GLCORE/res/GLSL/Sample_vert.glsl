#version 330 core

layout (location = 0) in vec3 attrPos;
layout (location = 1) in vec3 attrColor;
layout (location = 2) in vec2 attrTexcel;

out vec4 aColor;
out vec2 aTexcel;

uniform vec4 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(attrPos, 1.f);
	aColor = vec4(attrColor, 1.f) * ourColor;
	aTexcel = attrTexcel;
}