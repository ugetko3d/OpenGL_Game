#include "Light.h"

unsigned int Light::directional_light_counter = 0;
unsigned int Light::point_light_counter = 0;
unsigned int Light::spot_light_counter = 0;

Light::Light()
{
}

Light::~Light()
{
}

Light::Type Light::getType()
{
	return type;
}

bool Light::is(Type type)
{
	return (this->type == type);
}

void Light::enable()
{
	enabled = true;
	switch (type)
	{
	case Type::DIRECTIONAL:
		directional_light_counter++;
	case Type::POINT:
		point_light_counter++;
	case Type::SPOT:
		spot_light_counter++;
	}

}

void Light::disable()
{
	enabled = false;
	switch (type)
	{
	case Type::DIRECTIONAL:
		directional_light_counter--;
	case Type::POINT:
		point_light_counter--;
	case Type::SPOT:
		spot_light_counter--;
	}
}

bool Light::isEnabled()
{
	return enabled;
}

bool Light::drawLight(const Shader& shader)
{
	if (is(Type::DIRECTIONAL) && enabled)
	{
		shader.setVec3("directionalLights[" + std::to_string(id) + "].direction", direction);
		shader.setVec3("directionalLights[" + std::to_string(id) + "].ambient", vec3::scale(colour, ambient));
		shader.setVec3("directionalLights[" + std::to_string(id) + "].diffuse", vec3::scale(colour, diffuse));
		shader.setVec3("directionalLights[" + std::to_string(id) + "].specular", vec3::scale(colour, specular));
		return true;
	}
	else if (is(Type::DIRECTIONAL) && !enabled)
	{
		shader.setVec3("directionalLights[" + std::to_string(id) + "].ambient", DISABLED);
		shader.setVec3("directionalLights[" + std::to_string(id) + "].diffuse", DISABLED);
		shader.setVec3("directionalLights[" + std::to_string(id) + "].specular", DISABLED);
		return true;
	}
	else if (is(Type::POINT) && enabled)
	{
		shader.setVec3("pointLights[" + std::to_string(id) + "].position", position);
		shader.setVec3("pointLights[" + std::to_string(id) + "].ambient", vec3::scale(colour, ambient));
		shader.setVec3("pointLights[" + std::to_string(id) + "].diffuse", vec3::scale(colour, diffuse));
		shader.setVec3("pointLights[" + std::to_string(id) + "].specular", vec3::scale(colour, specular));
		shader.setFloat("pointLights[" + std::to_string(id) + "].constant", constant);
		shader.setFloat("pointLights[" + std::to_string(id) + "].linear", linear);
		shader.setFloat("pointLights[" + std::to_string(id) + "].quadratic", quadratic);
		return true;
	}
	else if (is(Type::POINT) && !enabled)
	{
		shader.setVec3("pointLights[" + std::to_string(id) + "].ambient", DISABLED);
		shader.setVec3("pointLights[" + std::to_string(id) + "].diffuse", DISABLED);
		shader.setVec3("pointLights[" + std::to_string(id) + "].specular", DISABLED);
		return true;
	}
	else if (is(Type::SPOT) && enabled)
	{
		shader.setVec3("spotLights[" + std::to_string(id) + "].position", position);
		shader.setVec3("spotLights[" + std::to_string(id) + "].direction", direction);
		shader.setVec3("spotLights[" + std::to_string(id) + "].ambient", ambient);
		shader.setVec3("spotLights[" + std::to_string(id) + "].diffuse", diffuse);
		shader.setVec3("spotLights[" + std::to_string(id) + "].specular", specular);
		shader.setFloat("spotLights[" + std::to_string(id) + "].constant", constant);
		shader.setFloat("spotLights[" + std::to_string(id) + "].linear", linear);
		shader.setFloat("spotLights[" + std::to_string(id) + "].quadratic", quadratic);
		shader.setFloat("spotLights[" + std::to_string(id) + "].cutOff", glm::cos(glm::radians(cutOff)));
		shader.setFloat("spotLights[" + std::to_string(id) + "].outerCutOff", glm::cos(glm::radians(outerCutOff)));
		return true;
	}
	else if (is(Type::SPOT) && !enabled)
	{
		shader.setVec3("spotLights[" + std::to_string(id) + "].ambient", DISABLED);
		shader.setVec3("spotLights[" + std::to_string(id) + "].diffuse", DISABLED);
		shader.setVec3("spotLights[" + std::to_string(id) + "].specular", DISABLED);
		return true;
	}
	return false;
}

bool Light::operator==(const Light& right) const
{
	return (this->type == right.type);
}

unsigned int Light::numDirectionalLights()
{
	return directional_light_counter;
}

unsigned int Light::numPointLights()
{
	return point_light_counter;
}

unsigned int Light::numSpotLights()
{
	return spot_light_counter;
}