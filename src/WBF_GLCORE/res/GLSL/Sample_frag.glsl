#version 330 core

out vec4 FragColor;

in vec4 aColor;
in vec2 aTexcel;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float fRatio;

void main()
{
	FragColor = mix(texture(ourTexture1, aTexcel), texture(ourTexture2, aTexcel), fRatio) * aColor;
}