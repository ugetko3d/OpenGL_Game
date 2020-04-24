#include <glew.h>

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

void VertexArray::SetAttribPointer(unsigned int attrib, unsigned int nFloats, unsigned int stride, unsigned int start)
{
	glVertexAttribPointer(attrib, nFloats, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(start * sizeof(float)));
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