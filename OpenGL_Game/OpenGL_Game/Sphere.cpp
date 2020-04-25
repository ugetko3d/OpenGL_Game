#include "Sphere.h"

Sphere::Sphere()
{
	createSphere(WIDTH, QUALITY);
}

Sphere::Sphere(float width, unsigned int quality)
{
	createSphere(width, quality);
}

Sphere::~Sphere()
{
}

void Sphere::createSphere(float width, unsigned int quality) {
	float radius = width / 2.0f;

	Diamond diamond = Diamond(width);
	
	vertices = diamond.vertices;
	uvs = diamond.uvs;
	subdivide(quality);

	for (int i = 0; i < vertices.size(); i++)
	{
		vertices.at(i).normalize();
		vertices.at(i) = vec3::scale(vertices.at(i), width);
	}
		
}