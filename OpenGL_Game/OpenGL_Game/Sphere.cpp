#include "Sphere.h"



Sphere::Sphere()
{
	loadObjectFile("resources/models/icosphere.model");
	setColour();
	calculateTangents();
}

Sphere::~Sphere()
{
}