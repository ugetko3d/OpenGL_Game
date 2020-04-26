#version 450 core
out vec4 FragColour;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
	vec4 result = texture(skybox, TexCoords);
	FragColour = vec4(result.x, result.y, result.z, 1.0);
}