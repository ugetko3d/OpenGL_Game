#include <glew.h>

#include "comm.h"
#include "vertex_array.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_VertexID);
	glBindVertexArray(m_VertexID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_VertexID);
}

void VertexArray::SetAttribPointer(uint32_t attrib, uint32_t nFloats, uint32_t stride, uint32_t start)
{
	glVertexAttribPointer(attrib, nFloats, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(start * sizeof(GLfloat)));
	glEnableVertexAttribArray(attrib);
}

void VertexArray::Bind()
{
	glBindVertexArray(m_VertexID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}