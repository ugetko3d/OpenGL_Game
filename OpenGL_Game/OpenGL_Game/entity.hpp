#pragma once

// Vertex attributes
const GLuint POSITION = 0;
const GLuint TEXTURE = 1;
const GLuint NORMAL = 2;

class Entity
{
public:
	GLuint vaoID;
	GLuint vboID;
	GLuint eboID;
	GLfloat* vertices;
	GLuint* indices;

	Entity(GLfloat* vertices, GLuint* indices);

	GLvoid createVAO();
	GLvoid bindVAO();
	GLvoid unbindVAO();

	GLvoid storeVertices();
	GLvoid storeIndices();
	GLvoid setAttribute(GLuint attribute, GLuint numFloats, GLuint dataBetween, GLuint dataStart);

	virtual GLvoid drawObject() = 0;

private:

};