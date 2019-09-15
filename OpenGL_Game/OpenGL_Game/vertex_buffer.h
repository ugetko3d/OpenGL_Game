#pragma once

class VertexBuffer
{
private:
	uint32_t m_BufferID;
public:
	VertexBuffer(float* vertices, uint32_t size);
	~VertexBuffer();

	void Bind();
	void Unbind();
};
