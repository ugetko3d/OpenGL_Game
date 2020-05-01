#pragma once

#include "Mesh.h"

// Dummy class that will receive Mesh data from an .obj file instead of computing the positions, texture coordinates, and normals
class Sphere : public Mesh
{
public:
	/* Constructor */
	Sphere();
	/* De-constructor */
	~Sphere();
};