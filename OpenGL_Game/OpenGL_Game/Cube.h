#pragma once
#include "Mesh.h"

class Cube : public Mesh
{
private:
	const float WIDTH = 1.0f, HEIGHT = 1.0f;
	/* Create a cube */
	void createCube(float width, float height);
public:
	/* Create a Cube object with default sizes. */
	Cube();
	/* Create a Cube object with width. */
	Cube(float width);
	/* Create a Cube object with width and height. */
	Cube(float width, float height);
	/* De-constructor */
	~Cube();
};