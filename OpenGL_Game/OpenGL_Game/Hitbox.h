#pragma once

#include "maths.h"
#include <algorithm>

class Hitbox
{
private:
	float clamp(float value, float min, float max);

public:
	bool isIntersecting = false;

	vec3 position;
	vec3 scale;
	vec3 rotation;

	Hitbox();

	void update(const vec3& p, const vec3& s);

	void checkCollision(const Hitbox& other);

	friend std::ostream& operator<<(std::ostream& stream, const Hitbox& h);

};