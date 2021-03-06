#pragma once
#include "Light.h"
class PointLight : public Light
{
private:
	const vec3 COLOUR = vec3(1.0f), POSITION = vec3(0.0f, 0.0f, 0.0f);
	const float AMBIENT = 0.05f, DIFFUSE = 0.8f, SPECULAR = 1.0f, CONSTANT = 1.0f, LINEAR = 0.09f, QUADRATIC = 0.032f;
public:
	/* Create pointlight */
	PointLight();
	/* Create pointlight */
	PointLight(const vec3& colour, const vec3& position);
	/* Create pointlight */
	PointLight(const vec3& colour, const vec3& position, float ambient, float diffuse, float specular);
	/* Create pointlight */
	PointLight(const vec3& colour, const vec3& position, float ambient, float diffuse, float specular, float constant, float linear, float quadratic);
	/* De-constructor */
	~PointLight();
};