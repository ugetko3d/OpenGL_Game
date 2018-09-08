#include <glew.h>

#include "entity.hpp"

Entity::Entity(GLfloat* vertices, GLuint* indices)
{
	this->vertices = vertices;
	this->indices = indices;
	createVAO();
	bindVAO();
	storeVertices();
	storeIndices();
	setAttribute(POSITION, 3, 8, 0);
	setAttribute(TEXTURE, 2, 8, 3);
	setAttribute(NORMAL, 3, 8, 5);
	unbindVAO();
}

GLvoid Entity::createVAO()
{
	glGenVertexArrays(1, &vaoID);
}

GLvoid Entity::bindVAO()
{
	glBindVertexArray(vaoID);
}

GLvoid Entity::unbindVAO()
{
	glBindVertexArray(0);
}

GLvoid Entity::storeVertices()
{
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

GLvoid Entity::storeIndices()
{
	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}

GLvoid Entity::setAttribute(GLuint attribute, GLuint numFloats, GLuint dataBetween, GLuint dataStart)
{
	glVertexAttribPointer(attribute, numFloats, GL_FLOAT, GL_FALSE, dataBetween * sizeof(GLfloat), (GLvoid*)(dataStart * sizeof(GLfloat)));
	glEnableVertexAttribArray(attribute);
}