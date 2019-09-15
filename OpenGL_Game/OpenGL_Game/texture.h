#pragma once

class Texture
{
private:
	uint32_t m_ID, m_width, m_height;
public:
	Texture(const std::string& path);
	~Texture();

	void Bind();
};

