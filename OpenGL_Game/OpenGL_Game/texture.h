#pragma once

class Texture
{
private:
	unsigned int m_texID;
	int m_width, m_height, m_channels;
	std::string m_filePath;
	unsigned char* m_texBuffer;
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot);
	void Unbind();
};

