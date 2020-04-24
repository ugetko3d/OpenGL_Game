#pragma once

class IndexBuffer
{
private:
	unsigned int m_BufferID, m_Count;
public:
	IndexBuffer(unsigned int* indices, unsigned int count);
	~IndexBuffer();

	void Bind();
	void Unbind();
};