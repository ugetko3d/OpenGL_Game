#pragma once
#include "Mesh.h"
class Triangle : public Mesh
{
private:
	const float WIDTH = 1.0f, HEIGHT = 1.0f;
public:
	/* Create a Triangle object that stores Mesh data */
	Triangle();
	/* Create a Triangle object that stores Mesh data */
	Triangle(float width);
	/* Create a Triangle object that stores Mesh data */
	Triangle(float width, float height);
	/* De-constructor */
	~Triangle();
	/* Create a triangle. */
	void createTriangle(float base, float height);
	/* Create a triangle. */
	void createTriangle(float side);
	/* Return height of triangle */
	float getHeight(float ground, float side);
	/* Return area of triangle */
	float getAreal(float base, float height);
};

