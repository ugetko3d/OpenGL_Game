#include "Material.h"


Material::Material()
{

}

Material::~Material()
{
}

void Material::addDiffuse(const Texture & texture)
{
	this->diffuse = texture;
	this->diffuseBound = true;
}

void Material::addSpecular(const Texture & texture)
{
	this->specular = texture;
	this->specularBound = true;
}

void Material::addNormal(const Texture & texture)
{
	this->normal = texture;
	this->normalBound = true;
}

void Material::addDisplacement(const Texture & texture)
{
	this->displacement = texture;
	this->displacementBound = true;
}

void Material::addAmbientOcclusion(const Texture & texture)
{
	this->ambient_occlusion = texture;
	this->AOBound = true;
}

const bool Material::hasDiffuse() {
	return diffuseBound;
}

const bool Material::hasSpecular()
{
	return specularBound;
}

const bool Material::hasNormal()
{
	return normalBound;
}

const bool Material::hasDisplacement()
{
	return displacementBound;
}

const bool Material::hasAO()
{
	return AOBound;
}

void Material::bind()
{
	if (diffuseBound) {
		diffuse.bind(0);
	}
	if (specularBound) {
		specular.bind(1);
	}
	if (normalBound) {
		normal.bind(2);
	}
	if (displacementBound) {
		displacement.bind(3);
	}
	if (AOBound) {
		ambient_occlusion.bind(4);
	}
}

void Material::unbind()
{
	if (diffuseBound) {
		diffuse.unbind();
	}
	if (specularBound) {
		specular.unbind();
	}
	if (normalBound) {
		normal.unbind();
	}
	if (displacementBound) {
		displacement.unbind();
	}
	if (AOBound) {
		ambient_occlusion.unbind();
	}
}