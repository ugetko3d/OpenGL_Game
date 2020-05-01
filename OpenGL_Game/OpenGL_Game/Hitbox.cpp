#include "Hitbox.h"
#pragma once

Hitbox::Hitbox()
{

}

void Hitbox::update(const vec3& p, const vec3& s)
{
	position = p;
	scale = s;
}

void Hitbox::checkCollision(const Hitbox& other)
{
	float aMinX = position.x - (scale.x / 2);
	float aMaxX = position.x + (scale.x / 2);
	float aMinY = position.y - (scale.y / 2);
	float aMaxY = position.y + (scale.y / 2);
	float aMinZ = position.z - (scale.z / 2);
	float aMaxZ = position.z + (scale.z / 2);

	float bMinX = other.position.x - (other.scale.x / 2);
	float bMaxX = other.position.x + (other.scale.x / 2);
	float bMinY = other.position.y - (other.scale.y / 2);
	float bMaxY = other.position.y + (other.scale.y / 2);
	float bMinZ = other.position.z - (other.scale.z / 2);
	float bMaxZ = other.position.z + (other.scale.z / 2);

	if ((aMinX <= bMaxX && aMaxX >= bMinX) &&
		(aMinY <= bMaxY && aMaxY >= bMinY) &&
		(aMinZ <= bMaxZ && aMaxZ >= bMinZ))
	{
		isIntersecting = true;
	}
	else
		isIntersecting = false;
}

float Hitbox::clamp(float value, float min, float max)
{
    return std::max(min, std::min(max, value));
}

std::ostream& operator<<(std::ostream& stream, const Hitbox& h)
{
	stream << "Hitbox: \n" <<
		"Position: " << h.position << "\n" <<
		"Scale: " << h.scale;
	return stream;
}