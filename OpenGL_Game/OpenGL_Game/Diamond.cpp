#include "Diamond.h"

Diamond::Diamond()
{
	createDiamond(WIDTH);
}

Diamond::Diamond(float width)
{
	createDiamond(width);
}

Diamond::~Diamond()
{
}

void Diamond::createDiamond(float width)
{
	float radius = width / 2.0f;

	indices = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23
	};

	vertices = {
		vec3(-radius, 0.0f, -radius),
		vec3(+radius, 0.0f, -radius),
		vec3(0.0f, +radius, 0.0f),

		vec3(+radius, 0.0f, -radius),
		vec3(+radius, 0.0f, +radius),
		vec3(0.0f, +radius, 0.0f),

		vec3(+radius, 0.0f, +radius),
		vec3(-radius, 0.0f, +radius),
		vec3(0.0f, +radius, 0.0f),

		vec3(-radius, 0.0f, +radius),
		vec3(-radius, 0.0f, -radius),
		vec3(0.0f, +radius, 0.0f),

		vec3(-radius, 0.0f, -radius),
		vec3(+radius, 0.0f, -radius),
		vec3(0.0f, -radius, 0.0f),

		vec3(+radius, 0.0f, -radius),
		vec3(+radius, 0.0f, +radius),
		vec3(0.0f, -radius, 0.0f),

		vec3(+radius, 0.0f, +radius),
		vec3(-radius, 0.0f, +radius),
		vec3(0.0f, -radius, 0.0f),

		vec3(-radius, 0.0f, +radius),
		vec3(-radius, 0.0f, -radius),
		vec3(0.0f, -radius, 0.0f)
	};

	normals = {
		vec3(0.0f, 0.5f, -0.5f),
		vec3(0.0f, 0.5f, -0.5f),
		vec3(0.0f, 0.5f, -0.5f),

		vec3(0.5f, 0.5f, 0.0f),
		vec3(0.5f, 0.5f, 0.0f),
		vec3(0.5f, 0.5f, 0.0f),

		vec3(0.0f, 0.5f, 0.5f),
		vec3(0.0f, 0.5f, 0.5f),
		vec3(0.0f, 0.5f, 0.5f),

		vec3(-0.5f, 0.5f, 0.0f),
		vec3(-0.5f, 0.5f, 0.0f),
		vec3(-0.5f, 0.5f, 0.0f),

		vec3(0.0f, -0.5f, -0.5f),
		vec3(0.0f, -0.5f, -0.5f),
		vec3(0.0f, -0.5f, -0.5f),

		vec3(0.5f, -0.5f, 0.0f),
		vec3(0.5f, -0.5f, 0.0f),
		vec3(0.5f, -0.5f, 0.0f),

		vec3(0.0f, -0.5f, 0.5f),
		vec3(0.0f, -0.5f, 0.5f),
		vec3(0.0f, -0.5f, 0.5f),

		vec3(-0.5f, -0.5f, 0.0f),
		vec3(-0.5f, -0.5f, 0.0f),
		vec3(-0.5f, -0.5f, 0.0f)
	};

	uvs = {
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f)
	};

	setColour();
	calculateTangents();
}