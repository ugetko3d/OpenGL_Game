#pragma once

class Texture
{
private:
	uint32_t m_texID, m_width, m_height;
public:
	Texture(const std::string& path);
	~Texture();

	static void Activate(GLenum textureUnit);
	void Bind();
	void Unbind();
};

