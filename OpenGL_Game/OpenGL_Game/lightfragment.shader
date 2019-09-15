#version 450 core

out vec4 FragColour;

in vec2 texCoord;
in vec3 normal;

uniform sampler2D sun;

void main()
{
	FragColour = texture(sun, texCoord);
}