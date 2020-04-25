#version 450 core

out vec4 FragColour;

in vec3 fragPos;
in vec2 texCoord;
in vec3 normal;

uniform sampler2D tex;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColour;

void main()
{
	// Ambient
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColour;

	// Diffuse 
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColour;

	// Specular
	float specularStrength = 0.7;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColour;

	// Adding all the lighting effects together
	vec3 result = (ambient + diffuse + specular);

	// Adding the lighting effects to the texture
	FragColour = texture(tex, texCoord) * vec4(result, 1.0);
}