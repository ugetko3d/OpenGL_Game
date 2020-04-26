#pragma once
#include "Light.h"

class SpotLight : public Light
{
private:
	const vec3 COLOUR = vec3(1.0f), POSITION = vec3(0.0f, 0.0f, 0.0f), DIRECTION = vec3(0.0f, -1.0f, 0.0f);
	const float AMBIENT = 0.05f, DIFFUSE = 0.8f, SPECULAR = 1.0f, CONSTANT = 1.0f, LINEAR = 0.09f, QUADRATIC = 0.032f, CUTOFF = 12.5f, OUTERCUTOFF = 15.0f;
public:
	/* Create spotlight. Use default parameters. */
	SpotLight();
	/* Create spotlight. */
	SpotLight(const vec3& colour, const vec3& position, const vec3& direction);
	/* Create spotlight. */
	SpotLight(const vec3& colour, const vec3& position, const vec3& direction, float ambient, float diffuse, float specular);
	/* Create spotlight. */
	SpotLight(const vec3& colour, const vec3& position, const vec3& direction, float ambient, float diffuse, float specular, float constant, float linear, float quadratic);
	/* Create spotlight. */
	SpotLight(const vec3& colour, const vec3& position, const vec3& direction, float ambient, float diffuse, float specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff);
	/* Sets position. */
	void setPosition(const vec3& position);
	/* Sets direction. */
	void setDirection(const vec3& direction);
	/* Deconstructor */
	~SpotLight();
};