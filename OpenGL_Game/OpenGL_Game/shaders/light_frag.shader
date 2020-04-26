#version 450 core

out vec4 FragColour;

uniform vec3 lightColour;
uniform bool hasLightColour;

void main()
{
	if (hasLightColour)
	{
		FragColour = vec4(lightColour, 1.0);
	}
	else
	{
		FragColour = vec4(1.0);
	}
}