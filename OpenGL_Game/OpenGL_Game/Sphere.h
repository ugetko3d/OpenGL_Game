#pragma once

#include "Vertex.h"
#include "Diamond.h"

/* https://stackoverflow.com/questions/7687148/drawing-sphere-in-opengl-without-using-glusphere */

class Sphere : public Vertex
{
private:
	const float WIDTH = 1.0f;
	const unsigned int QUALITY = 4;
	/* Creates the sphere. */
	void createSphere(float width, unsigned int quality);
public:
	/* Create a Sphere object that stores vertex data. Uses default size. */
	Sphere();
	/* Create a Sphere object that stores vertex data. Specify width and quality. */
	Sphere(float width, unsigned int quality);
	/* De-constructor */
	~Sphere();
};