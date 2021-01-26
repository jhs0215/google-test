#version 330 core

out vec4 FragColor;

in vec2 aFragTexcel;

uniform sampler2D texture_diffuse;

void main()
{
	FragColor = vec4(texture(texture_diffuse, aFragTexcel).rgb, 1.f);
	//FragColor = vec4(aFragTexcel, 0.f, 1.f);
}