#include "PointLight.h"

PointLight::PointLight()
{
	this->type = Type::POINT;
	this->id = point_light_counter++;
	this->colour = COLOUR;
	this->position = POSITION;
	this->ambient = AMBIENT;
	this->diffuse = DIFFUSE;
	this->specular = SPECULAR;
	this->constant = CONSTANT;
	this->linear = LINEAR;
	this->quadratic = QUADRATIC;
}

PointLight::PointLight(const vec3& colour, const vec3& position)
{
	this->type = Type::POINT;
	this->id = point_light_counter++;
	this->colour = colour;
	this->position = position;
	this->ambient = AMBIENT;
	this->diffuse = DIFFUSE;
	this->specular = SPECULAR;
	this->constant = CONSTANT;
	this->linear = LINEAR;
	this->quadratic = QUADRATIC;
}

PointLight::PointLight(const vec3& colour, const vec3& position, float ambient, float diffuse, float specular)
{
	this->type = Type::POINT;
	this->id = point_light_counter++;
	this->colour = colour;
	this->position = position;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = CONSTANT;
	this->linear = LINEAR;
	this->quadratic = QUADRATIC;
}

PointLight::PointLight(const vec3& colour, const vec3& position, float ambient, float diffuse, float specular, float constant, float linear, float quadratic)
{
	this->type = Type::POINT;
	this->id = point_light_counter++;
	this->colour = colour;
	this->position = position;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

PointLight::~PointLight()
{
}