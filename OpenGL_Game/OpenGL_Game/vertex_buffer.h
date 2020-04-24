#pragma once

class VertexBuffer
{
private:
	unsigned int m_BufferID;
public:
	VertexBuffer(float* vertices, unsigned int size);
	~VertexBuffer();

	void Bind();
	void Unbind();
};
