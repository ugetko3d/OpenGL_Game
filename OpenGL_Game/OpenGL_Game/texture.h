#pragma once

class Texture
{
private:
	unsigned int m_texID, m_width, m_height;
public:
	Texture(const std::string& path);
	~Texture();

	static void Activate(unsigned int textureUnit);
	void Bind();
	void Unbind();
};

