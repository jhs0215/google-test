#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexcel;

struct TMatrix
{
	mat4 matModel;
	mat4 matView;
	mat4 matProjection;
	mat4 matNormal;
};

out vec3 aFragPos;
out vec3 aFragNormal;
out vec2 aFragTexcel;

uniform TMatrix tMatrix;

void main()
{	
	mat4 matModelView = tMatrix.matView * tMatrix.matModel;
	mat4 matModelViewProjection = tMatrix.matProjection * tMatrix.matView * tMatrix.matModel;

	aFragPos = vec3(matModelView * vec4(aPos, 1.f));
	aFragNormal = vec3(tMatrix.matNormal * vec4(aNormal, 1.f));
	aFragTexcel = aTexcel;

	gl_Position = matModelViewProjection * vec4(aPos, 1.f);
}