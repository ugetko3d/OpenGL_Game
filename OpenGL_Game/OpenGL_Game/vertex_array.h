#pragma once

class VertexArray
{
private:
	unsigned int m_VertexID;
public:
	VertexArray();
	~VertexArray();

	void SetAttribPointer(unsigned int attrib, unsigned int nFloats, unsigned int stride, unsigned int start);

	void Bind();
	void Unbind();
};