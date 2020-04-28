#pragma once

#include "Vertex.h"

// Dummy class that will receive vertex data from an .obj file instead of computing the positions, texture coordinates, and normals
class Sphere : public Vertex
{
public:
	/* Constructor */
	Sphere();
	/* De-constructor */
	~Sphere();
};