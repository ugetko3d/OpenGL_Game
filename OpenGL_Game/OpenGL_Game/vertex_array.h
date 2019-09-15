#pragma once

class VertexArray
{
private:
	uint32_t m_VertexID;
public:
	VertexArray();
	~VertexArray();

	void SetAttribPointer(uint32_t attrib, uint32_t nFloats, uint32_t stride, uint32_t start);

	void Bind();
	void Unbind();
};