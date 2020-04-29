#include "Vertex.h"

Vertex::Vertex(const std::vector<vec3>& vertices, const std::vector<vec3>& normals, const std::vector<vec3>& colours, const std::vector<vec2>& uvs, const std::vector<vec3>& tangents, const std::vector<vec3>& bitangents, const std::vector<unsigned short>& indices)
{
	this->vertices = vertices;
	this->normals = normals;
	this->colours = colours;
	this->uvs = uvs;
	this->tangents = tangents;
	this->bitangents = bitangents;
	this->indices = indices;
}

Vertex::~Vertex()
{
	if (storedOnGPU)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
}

void Vertex::setScale(const vec3& scale_vector)
{
	scale.scale(scale_vector);
	uv_scale.x = scale_vector.x;
	uv_scale.y = scale_vector.y;
}

mat4& Vertex::getScale()
{
	return scale;
}

vec2& Vertex::getUVScale()
{
	return uv_scale;
}

void Vertex::setRotate(float rotate_degrees, const vec3& rotate_vector)
{
	rotate.rotate(rotate_degrees, rotate_vector);
}

mat4& Vertex::getRotation()
{
	return rotate;
}

void Vertex::setTranslate(const vec3& position_vector)
{
	translate.translate(position_vector);
}

mat4& Vertex::getTranslate()
{
	return translate;
}

const unsigned int Vertex::size()
{
	return dataSize() / stride();
}

const unsigned int Vertex::dataSize()
{
	return vertices.size() * 3 + normals.size() * 3 + colours.size() * 3 + uvs.size() * 2 + tangents.size() * 3 + bitangents.size() * 3;
}

bool Vertex::hasVertices()
{
	return !vertices.empty();
}

bool Vertex::hasNormals()
{
	return !normals.empty();
}

bool Vertex::hasColours()
{
	return !colours.empty();
}

bool Vertex::hasUVs()
{
	return !uvs.empty();
}

bool Vertex::hasTangents()
{
	return !tangents.empty();
}

bool Vertex::hasBitangents()
{
	return !bitangents.empty();
}

bool Vertex::hasIndices()
{
	return !indices.empty();
}

const unsigned int Vertex::stride()
{
	unsigned int stride = 0;
	if (hasVertices()) stride += 3;
	if (hasNormals()) stride += 3;
	if (hasColours()) stride += 3;
	if (hasUVs()) stride += 2;
	if (hasTangents()) stride += 3;
	if (hasBitangents()) stride += 3;
	return stride;
}

const unsigned int Vertex::verticeStride()
{
	return 0;
}

const unsigned int Vertex::normalStride()
{
	unsigned int stride = 3;
	if (!hasVertices()) stride -= 3;
	return stride;
}

const unsigned int Vertex::colourStride()
{
	unsigned int stride = 6;
	if (!hasVertices()) stride -= 3;
	if (!hasNormals()) stride -= 3;
	return stride;
}

const unsigned int Vertex::uvStride()
{
	unsigned int stride = 9;
	if (!hasVertices()) stride -= 3;
	if (!hasNormals()) stride -= 3;
	if (!hasColours()) stride -= 3;
	return stride;
}

const unsigned int Vertex::tangentStride()
{
	unsigned int stride = 11;
	if (!hasVertices()) stride -= 3;
	if (!hasNormals()) stride -= 3;
	if (!hasColours()) stride -= 3;
	if (!hasUVs()) stride -= 2;
	return stride;
}

const unsigned int Vertex::bitangentStride()
{
	unsigned int stride = 14;
	if (!hasVertices()) stride -= 3;
	if (!hasNormals()) stride -= 3;
	if (!hasColours()) stride -= 3;
	if (!hasUVs()) stride -= 2;
	if (!hasTangents()) stride -= 3;
	return stride;
}

bool Vertex::storeOnGPU()
{
	if (hasVertices() && m_isModelParsed)
	{
		glGenVertexArrays(1, &VAO); // Create VAO that stores the buffer objects.
		glGenBuffers(1, &VBO); // Create VBO that stores vertex data
		glGenBuffers(1, &EBO); // Create EBO that stores indices
		glBindVertexArray(VAO); // Bind the VAO before binding and configuring buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the VBO to the GL_ARRAY_BUFFER target								
		// Copy vertex data into the VBO currently bound to the GL_ARRAY_BUFFER target
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * dataSize(), data().data(), GL_STATIC_DRAW);

		const unsigned int stride = this->stride() * sizeof(float);

		if (hasVertices())
		{
			// Position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(verticeStride() * sizeof(float)));
			glEnableVertexAttribArray(0);
		}
		if (hasNormals())
		{
			// Normals coordinate attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(normalStride() * sizeof(float)));
			glEnableVertexAttribArray(1);
		}
		if (hasColours())
		{
			// Colours coordinate attribute
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(colourStride() * sizeof(float)));
			glEnableVertexAttribArray(2);
		}
		if (hasUVs())
		{
			// Texture coordinate attribute
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride, (void*)(uvStride() * sizeof(float)));
			glEnableVertexAttribArray(3);
		}
		if (hasTangents())
		{
			// Tangents coordinate attribute
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (void*)(tangentStride() * sizeof(float)));
			glEnableVertexAttribArray(4);
		}
		if (hasBitangents())
		{
			// Tangents coordinate attribute
			glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, stride, (void*)(bitangentStride() * sizeof(float)));
			glEnableVertexAttribArray(5);
		}
		if (hasIndices())
		{
			// Bind the EBO to the GL_ELEMENT_ARRAY_BUFFER target
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			// Copy indices data into the EBO currently bound to the GL_ELEMENT_ARRAY_BUFFER target
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), indices.data(), GL_STATIC_DRAW);
		}

		storedOnGPU = true;
		return true;
	}
	else
	{
		std::cout << "Mesh : storeOnGPU() : Cannot store vertex data on GPU. Vertex data is empty!";
		return false;
	}
}

void Vertex::setDrawMode(GLenum mode)
{
	draw_mode = mode;
}

void Vertex::scaleTextures(bool enable)
{
	scaleTexture = enable;
}

bool Vertex::drawObject(const Shader& shader, const vec3& position, const vec3& scale_vector, float rotation_degrees, const vec3& rotation_vector, Material* material)
{
	if (storedOnGPU)
	{
		// Bind textures
		if (material)
			material->bind();

		// Bind VAO
		glBindVertexArray(VAO);

		// Calculate the model matrix for each object and pass it to shader before drawing
		translate.translate(position);
		rotate.rotate(rotation_degrees, rotation_vector);
		scale.scale(scale_vector);
		mat4 model = translate * rotate * scale;
		shader.setMat4("model", model);

		if (scaleTexture)
			shader.setVec2("scale", vec2(scale_vector.x * uv_scale.x, scale_vector.y * uv_scale.y));
		else
			shader.setVec2("scale", vec2(1.0f, 1.0f));

		// Draw mesh
		glDrawElements(draw_mode, indices.size(), GL_UNSIGNED_SHORT, 0);

		// Unbind textures
		if (material)
			material->unbind();

		return true;
	}
	else
	{
		std::cout << "Mesh : drawObject() : Can't draw modle. Vertex data is not stored on GPU. Call storeOnGPU() first!";
		return false;
	}
}

bool Vertex::drawObject(const Shader& shader, const vec3& position, float rotation_degrees, const vec3& rotation_vector, Material* material)
{
	return drawObject(shader, position, vec3(1.0f), rotation_degrees, rotation_vector, material);
}

bool Vertex::drawObject(const Shader& shader, const vec3& position, const vec3& scale_vector, Material* material)
{
	return drawObject(shader, position, scale_vector, 0.0f, vec3(1.0f), material);
}

bool Vertex::drawObject(const Shader& shader, const vec3& position, Material* material)
{
	return drawObject(shader, position, vec3(1.0f), 0.0f, vec3(1.0f), material);
}

bool Vertex::drawObject(const Shader& shader, Material* material)
{
	return drawObject(shader, vec3(0.0f), vec3(1.0f), 0.0f, vec3(1.0f), material);
}

void Vertex::printVertices()
{
	for (vec3 v : vertices)
		std::cout << v << std::endl;
}

void Vertex::printNormals()
{
	for (vec3 v : normals)
		std::cout << v << std::endl;
}

void Vertex::printColours()
{
	for (vec3 v : colours)
		std::cout << v << std::endl;
}

void Vertex::printUVs()
{
	for (vec2 v : uvs)
		std::cout << v << std::endl;
}

void Vertex::printTangents()
{
	for (vec3 v : tangents)
		std::cout << v << std::endl;
}

void Vertex::printBitangents()
{
	for (vec3 v : bitangents)
		std::cout << v << std::endl;
}

void Vertex::printIndices()
{
	for (unsigned int i = 0; i < indices.size(); i += 3)
		std::cout << indices[i] << ", " << indices[i + 1] << ", " << indices[i + 2] << std::endl;
}

void Vertex::printVertexData()
{
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (hasVertices())
			std::cout << "Vertices(" << vertices[i].x << ", " << vertices[i].y << ", " << vertices[i].z << "), ";
		if (hasNormals())
			std::cout << "Normals(" << normals[i].x << ", " << normals[i].y << ", " << normals[i].z << "), ";
		if (hasColours())
			std::cout << "Colours(" << colours[i].x << ", " << colours[i].y << ", " << colours[i].z << "), ";
		if (hasUVs())
			std::cout << "UVs(" << uvs[i].x << ", " << uvs[i].y << "), ";
		if (hasTangents())
			std::cout << "Tangents(" << tangents[i].x << ", " << tangents[i].y << ", " << tangents[i].z << ")";
		if (hasBitangents())
			std::cout << "Bitangents(" << bitangents[i].x << ", " << bitangents[i].y << ", " << bitangents[i].z << ")";
		std::cout << std::endl << std::endl;
	}
}

void Vertex::printDataSizes()
{
	std::cout << "Vertices: " << vertices.size() << std::endl;
	std::cout << "Normals: " << normals.size() << std::endl;
	std::cout << "Colour: " << colours.size() << std::endl;
	std::cout << "UVs: " << uvs.size() << std::endl;
	std::cout << "Tangents: " << tangents.size() << std::endl;
	std::cout << "Bitangents: " << bitangents.size() << std::endl;
	std::cout << "Indices: " << indices.size() << std::endl;
}

std::vector<float> Vertex::data()
{
	std::vector<float> raw_data;
	
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (hasVertices())
		{
			raw_data.push_back(vertices.at(i).x);
			raw_data.push_back(vertices.at(i).y);
			raw_data.push_back(vertices.at(i).z);
		}
		if (hasNormals())
		{
			raw_data.push_back(normals.at(i).x);
			raw_data.push_back(normals.at(i).y);
			raw_data.push_back(normals.at(i).z);
		}
		if (hasColours())
		{
			raw_data.push_back(colours.at(i).x);
			raw_data.push_back(colours.at(i).y);
			raw_data.push_back(colours.at(i).z);
		}
		if (hasUVs())
		{
			raw_data.push_back(uvs.at(i).x);
			raw_data.push_back(uvs.at(i).y);
		}
		if (hasTangents())
		{
			raw_data.push_back(tangents.at(i).x);
			raw_data.push_back(tangents.at(i).y);
			raw_data.push_back(tangents.at(i).z);
		}
		if (hasBitangents())
		{
			raw_data.push_back(bitangents.at(i).x);
			raw_data.push_back(bitangents.at(i).y);
			raw_data.push_back(bitangents.at(i).z);
		}
	}

	return raw_data;
}

void Vertex::setColour(const vec3& colour)
{
	colours = std::vector<vec3>(size(), colour);
}

void Vertex::calculateTangents()
{

	// Remove any previous tangents and bitangents
	tangents.clear();
	bitangents.clear();

	if (hasIndices())
	{
		for (unsigned int i = 0; i < indices.size(); i += 3)
		{
			// Shortcuts for vertices
			vec3 p1 = vertices.at(indices.at(i + 0));
			vec3 p2 = vertices.at(indices.at(i + 1));
			vec3 p3 = vertices.at(indices.at(i + 2));

			// Shortcuts for UVs
			vec2 uv1 = uvs.at(indices.at(i + 0));
			vec2 uv2 = uvs.at(indices.at(i + 1));
			vec2 uv3 = uvs.at(indices.at(i + 2));

			// Edges of the triangle : postion delta
			vec3 deltaPos1 = p2 - p1;
			vec3 deltaPos2 = p3 - p1;

			// UV delta
			vec2 deltaUV1 = uv2 - uv1;
			vec2 deltaUV2 = uv3 - uv1;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
			vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
			vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

			// Set the same tangent for all three vertices of the triangle.
			// They will be merged later, in vboindexer.cpp
			tangents.push_back(tangent);
			tangents.push_back(tangent);
			tangents.push_back(tangent);

			// Same thing for binormals
			bitangents.push_back(bitangent);
			bitangents.push_back(bitangent);
			bitangents.push_back(bitangent);
		}
	}
	else
	{
		for (unsigned int i = 0; i < size(); i += 3)
		{
			// Shortcuts for vertices
			vec3 p1 = vertices.at(i + 0);
			vec3 p2 = vertices.at(i + 1);
			vec3 p3 = vertices.at(i + 2);

			// Shortcuts for UVs
			vec2 uv1 = uvs.at(i + 0);
			vec2 uv2 = uvs.at(i + 1);
			vec2 uv3 = uvs.at(i + 2);

			// Edges of the triangle : postion delta
			vec3 deltaPos1 = p2 - p1;
			vec3 deltaPos2 = p3 - p1;

			// UV delta
			vec2 deltaUV1 = uv2 - uv1;
			vec2 deltaUV2 = uv3 - uv1;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
			vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
			vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

			// Set the same tangent for all three vertices of the triangle.
			// They will be merged later, in vboindexer.cpp
			tangents.push_back(tangent);
			tangents.push_back(tangent);
			tangents.push_back(tangent);

			// Same thing for binormals
			bitangents.push_back(bitangent);
			bitangents.push_back(bitangent);
			bitangents.push_back(bitangent);
		}
	}
}


void Vertex::loadObjectFile(const std::string& filePath)
{
	std::vector<vec3> temp_vertices, temp_normals;
	std::vector<vec2> temp_uvs;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

	FILE* file = fopen(filePath.c_str(), "r");
	if (file == NULL)
	{
		std::cout << "Unable to open .obj file at: " << filePath << std::endl;
		m_isModelParsed = false;
		return;
	}

	while(1)
	{

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.


		if (strcmp(lineHeader, "v") == 0) // Vertex position
		{
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) // Vertex texture coordinate
		{
			vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			//uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) // Vertex normal
		{
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				std::cout << "A line starting with \"f\" does not seem to contain 9 float values. Check the .obj file!" << std::endl;
				fclose(file);
				m_isModelParsed = false;
				return;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
	
		}
		else
		{
			// Probably a comment, store the rest of the line in a dummy buffer
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	fclose(file);

	m_isModelParsed = true;

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		vec3 vertex = temp_vertices[vertexIndex - 1];
		vec2 uv = temp_uvs[uvIndex - 1];
		vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		vertices.push_back(vertex);
		uvs.push_back(uv);
		normals.push_back(normal);
		indices.push_back(i);
	}

}

