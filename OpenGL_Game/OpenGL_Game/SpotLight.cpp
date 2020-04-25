#include "SpotLight.h"

SpotLight::SpotLight()
{
	this->type = Type::SPOT;
	this->id = spot_light_counter++;
	this->color = COLOR;
	this->position = POSITION;
	this->direction = DIRECTION;
	this->ambient = AMBIENT;
	this->diffuse = DIFFUSE;
	this->specular = SPECULAR;
	this->constant = CONSTANT;
	this->linear = LINEAR;
	this->quadratic = QUADRATIC;
	this->cutOff = CUTOFF;
	this->outerCutOff = OUTERCUTOFF;
}

SpotLight::SpotLight(const vec3& color, const vec3& position, const vec3& direction)
{
	this->type = Type::SPOT;
	this->id = spot_light_counter++;
	this->color = color;
	this->position = position;
	this->direction = direction;
	this->ambient = AMBIENT;
	this->diffuse = DIFFUSE;
	this->specular = SPECULAR;
	this->constant = CONSTANT;
	this->linear = LINEAR;
	this->quadratic = QUADRATIC;
	this->cutOff = CUTOFF;
	this->outerCutOff = OUTERCUTOFF;
}

SpotLight::SpotLight(const vec3& color, const vec3& position, const vec3& direction, float ambient, float diffuse, float specular)
{
	this->type = Type::SPOT;
	this->id = spot_light_counter++;
	this->color = color;
	this->position = position;
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = CONSTANT;
	this->linear = LINEAR;
	this->quadratic = QUADRATIC;
	this->cutOff = CUTOFF;
	this->outerCutOff = OUTERCUTOFF;
}

SpotLight::SpotLight(const vec3& color, const vec3& position, const vec3& direction, float ambient, float diffuse, float specular, float constant, float linear, float quadratic)
{
	this->type = Type::SPOT;
	this->id = spot_light_counter++;
	this->color = color;
	this->position = position;
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->cutOff = CUTOFF;
	this->outerCutOff = OUTERCUTOFF;
}

SpotLight::SpotLight(const vec3& color, const vec3& position, const vec3& direction, float ambient, float diffuse, float specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff)
{
	this->type = Type::SPOT;
	this->id = spot_light_counter++;
	this->color = color;
	this->position = position;
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
}

SpotLight::~SpotLight()
{
}
