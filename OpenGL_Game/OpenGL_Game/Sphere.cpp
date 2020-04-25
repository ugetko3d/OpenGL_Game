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

	for (vec3 v: vertices)
	{
		v.normalize();
		v = vec3::scale(v, width);
	}
		
}