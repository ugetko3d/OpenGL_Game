#version 450 core

out vec4 FragColour;

in vec2 texCoord;
in vec3 normal;

uniform sampler2D tex;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	FragColour = texture(tex, texCoord);
}