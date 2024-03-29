#pragma once
#include <glew.h>
#include <glfw3.h>
#include "stb_image.h"
#include "maths.h"
#include "Shader.h"
#include <iostream>
#include <vector>

class CubeMap
{
private:
	unsigned int m_id, m_VAO, m_VBO;
	const float VERTICES[108] = {
		-1.0f,	+1.0f,	-1.0f,
		-1.0f,	-1.0f,	-1.0f,
		+1.0f,	-1.0f,	-1.0f,
		+1.0f,	-1.0f,	-1.0f,
		+1.0f,	+1.0f,	-1.0f,
		-1.0f,	+1.0f,	-1.0f,

		-1.0f,	-1.0f,	+1.0f,
		-1.0f,	-1.0f,	-1.0f,
		-1.0f,	+1.0f,	-1.0f,
		-1.0f,	+1.0f,	-1.0f,
		-1.0f,	+1.0f,	+1.0f,
		-1.0f,	-1.0f,	+1.0f,

		+1.0f,	-1.0f,	-1.0f,
		+1.0f,	-1.0f,	+1.0f,
		+1.0f,	+1.0f,	+1.0f,
		+1.0f,	+1.0f,	+1.0f,
		+1.0f,	+1.0f,	-1.0f,
		+1.0f,	-1.0f,	-1.0f,

		-1.0f,	-1.0f,	+1.0f,
		-1.0f,	+1.0f,	+1.0f,
		+1.0f,	+1.0f,	+1.0f,
		+1.0f,	+1.0f,	+1.0f,
		+1.0f,	-1.0f,	+1.0f,
		-1.0f,	-1.0f,	+1.0f,

		-1.0f,	+1.0f,	-1.0f,
		+1.0f,	+1.0f,	-1.0f,
		+1.0f,	+1.0f,	+1.0f,
		+1.0f,	+1.0f,	+1.0f,
		-1.0f,	+1.0f,	+1.0f,
		-1.0f,	+1.0f,	-1.0f,

		-1.0f,	-1.0f,	-1.0f,
		-1.0f,	-1.0f,	+1.0f,
		+1.0f,	-1.0f,	-1.0f,
		+1.0f,	-1.0f,	-1.0f,
		-1.0f,	-1.0f,	+1.0f,
		+1.0f,	-1.0f,	+1.0f
	};
public:
	/* Default constructor */
	CubeMap();
	/* De-constructor */
	~CubeMap();
	/* Generate buffers and store vertex data on the GPU. Call drawCubemap(...) to draw it */
	void storeOnGPU();
	/* Load cubemap texture and attach it. You must provide a string-vector of 6 filepaths */
	void loadCubemapTexture(const std::vector<std::string>& faces);
	/* Load cubemap texture and attach it. You must provide 6 filepaths as Strings */
	void loadCubemapTexture(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& front, const std::string& back);
	/* Draws the cubemap from vertex data stored on the GPU */
	void drawCubemap(Shader& shader, mat4& view, mat4& projection);
};