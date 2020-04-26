#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	this->type = Type::DIRECTIONAL;
	this->id = directional_light_counter++;
	this->colour = COLOUR;
	this->direction = DIRECTION;
	this->ambient = AMBIENT;
	this->diffuse = DIFFUSE;
	this->specular = SPECULAR;
}

DirectionalLight::DirectionalLight(const vec3& colour, const vec3& direction)
{
	this->type = Type::DIRECTIONAL;
	this->id = directional_light_counter++;
	this->colour = colour;
	this->direction = direction;
	this->ambient = AMBIENT;
	this->diffuse = DIFFUSE;
	this->specular = SPECULAR;
}

DirectionalLight::DirectionalLight(const vec3& colour, const vec3& direction, float ambient, float diffuse, float specular)
{
	this->type = Type::DIRECTIONAL;
	this->id = directional_light_counter++;
	this->colour = colour;
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

DirectionalLight::~DirectionalLight()
{
}
