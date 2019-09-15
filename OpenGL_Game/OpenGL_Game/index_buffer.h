#pragma once

class IndexBuffer
{
private:
	uint32_t m_BufferID, m_Count;
public:
	IndexBuffer(uint32_t* indices, uint32_t count);
	~IndexBuffer();

	void Bind();
	void Unbind();
};