#include "Mesh.h"

Mesh::Mesh(const std::vector<vec3>& vertices, const std::vector<vec3>& normals, const std::vector<vec3>& colours, const std::vector<vec2>& uvs, const std::vector<vec3>& tangents, const std::vector<vec3>& bitangents, const std::vector<unsigned int>& indices)
{
	this->vertices = vertices;
	this->normals = normals;
	this->colours = colours;
	this->uvs = uvs;
	this->tangents = tangents;
	this->bitangents = bitangents;
	this->indices = indices;
}

Mesh::~Mesh()
{
	if (storedOnGPU)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
}

void Mesh::setScale(const vec3& scale_vector)
{
	hitbox.scale = scale_vector;
	scale.scale(scale_vector);
	uv_scale.x = scale_vector.x;
	uv_scale.y = scale_vector.y;
}

mat4& Mesh::getScale()
{
	return scale;
}

vec2& Mesh::getUVScale()
{
	return uv_scale;
}

void Mesh::setRotate(float rotate_degrees, const vec3& rotate_vector)
{
	hitbox.rotation = rotate_vector;
	rotate.rotate(rotate_degrees, rotate_vector);
}

mat4& Mesh::getRotation()
{
	return rotate;
}

void Mesh::setTranslate(const vec3& position_vector)
{
	hitbox.position = position_vector;
	translate.translate(position_vector);
}

mat4& Mesh::getTranslate()
{
	return translate;
}

const unsigned int Mesh::size()
{
	return dataSize() / stride();
}

const unsigned int Mesh::dataSize()
{
	return vertices.size() * 3 + normals.size() * 3 + colours.size() * 3 + uvs.size() * 2 + tangents.size() * 3 + bitangents.size() * 3;
}

bool Mesh::hasVertices()
{
	return !vertices.empty();
}

bool Mesh::hasNormals()
{
	return !normals.empty();
}

bool Mesh::hasColours()
{
	return !colours.empty();
}

bool Mesh::hasUVs()
{
	return !uvs.empty();
}

bool Mesh::hasTangents()
{
	return !tangents.empty();
}

bool Mesh::hasBitangents()
{
	return !bitangents.empty();
}

bool Mesh::hasIndices()
{
	return !indices.empty();
}

const unsigned int Mesh::stride()
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

const unsigned int Mesh::verticeStride()
{
	return 0;
}

const unsigned int Mesh::normalStride()
{
	unsigned int stride = 3;
	if (!hasVertices()) stride -= 3;
	return stride;
}

const unsigned int Mesh::colourStride()
{
	unsigned int stride = 6;
	if (!hasVertices()) stride -= 3;
	if (!hasNormals()) stride -= 3;
	return stride;
}

const unsigned int Mesh::uvStride()
{
	unsigned int stride = 9;
	if (!hasVertices()) stride -= 3;
	if (!hasNormals()) stride -= 3;
	if (!hasColours()) stride -= 3;
	return stride;
}

const unsigned int Mesh::tangentStride()
{
	unsigned int stride = 11;
	if (!hasVertices()) stride -= 3;
	if (!hasNormals()) stride -= 3;
	if (!hasColours()) stride -= 3;
	if (!hasUVs()) stride -= 2;
	return stride;
}

const unsigned int Mesh::bitangentStride()
{
	unsigned int stride = 14;
	if (!hasVertices()) stride -= 3;
	if (!hasNormals()) stride -= 3;
	if (!hasColours()) stride -= 3;
	if (!hasUVs()) stride -= 2;
	if (!hasTangents()) stride -= 3;
	return stride;
}

bool Mesh::storeOnGPU()
{
	if (hasVertices() && m_isModelLoaded)
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
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
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

void Mesh::setDrawMode(GLenum mode)
{
	draw_mode = mode;
}

void Mesh::scaleTextures(bool enable)
{
	scaleTexture = enable;
}

bool Mesh::drawObject(const Shader& shader, const vec3& position, const vec3& scale_vector, float rotation_degrees, const vec3& rotation_vector, Material* material)
{
	if (storedOnGPU)
	{
		// Bind textures
		if (material)
			material->bind();

		// Bind VAO
		glBindVertexArray(VAO);

		// Calculate the model matrix for each object and pass it to shader before drawing
		setTranslate(position);
		setRotate(rotation_degrees, rotation_vector);
		setScale(scale_vector);
		mat4 model = translate * rotate * scale;
		shader.setMat4("model", model);

		hitbox.update(position, scale_vector);

		if (scaleTexture)
			shader.setVec2("scale", vec2(scale_vector.x * uv_scale.x, scale_vector.y * uv_scale.y));
		else
			shader.setVec2("scale", vec2(1.0f, 1.0f));

		// Draw mesh
		glDrawElements(draw_mode, indices.size(), GL_UNSIGNED_INT, 0);

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

bool Mesh::drawObject(const Shader& shader, const vec3& position, float rotation_degrees, const vec3& rotation_vector, Material* material)
{
	return drawObject(shader, position, vec3(1.0f), rotation_degrees, rotation_vector, material);
}

bool Mesh::drawObject(const Shader& shader, const vec3& position, const vec3& scale_vector, Material* material)
{
	return drawObject(shader, position, scale_vector, 0.0f, vec3(1.0f), material);
}

bool Mesh::drawObject(const Shader& shader, const vec3& position, Material* material)
{
	return drawObject(shader, position, vec3(1.0f), 0.0f, vec3(1.0f), material);
}

bool Mesh::drawObject(const Shader& shader, Material* material)
{
	return drawObject(shader, vec3(0.0f), vec3(1.0f), 0.0f, vec3(1.0f), material);
}

void Mesh::printVertices()
{
	for (vec3 v : vertices)
		std::cout << v << std::endl;
}

void Mesh::printNormals()
{
	for (vec3 v : normals)
		std::cout << v << std::endl;
}

void Mesh::printColours()
{
	for (vec3 v : colours)
		std::cout << v << std::endl;
}

void Mesh::printUVs()
{
	for (vec2 v : uvs)
		std::cout << v << std::endl;
}

void Mesh::printTangents()
{
	for (vec3 v : tangents)
		std::cout << v << std::endl;
}

void Mesh::printBitangents()
{
	for (vec3 v : bitangents)
		std::cout << v << std::endl;
}

void Mesh::printIndices()
{
	for (unsigned int i = 0; i < indices.size(); i += 3)
		std::cout << indices[i] << ", " << indices[i + 1] << ", " << indices[i + 2] << std::endl;
}

void Mesh::printMeshData()
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

void Mesh::printDataSizes()
{
	std::cout << "Vertices: " << vertices.size() << std::endl;
	std::cout << "Normals: " << normals.size() << std::endl;
	std::cout << "Colour: " << colours.size() << std::endl;
	std::cout << "UVs: " << uvs.size() << std::endl;
	std::cout << "Tangents: " << tangents.size() << std::endl;
	std::cout << "Bitangents: " << bitangents.size() << std::endl;
	std::cout << "Indices: " << indices.size() << std::endl;
}

std::vector<float> Mesh::data()
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

void Mesh::setColour(const vec3& colour)
{
	colours = std::vector<vec3>(size(), colour);
}

void Mesh::calculateTangents()
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


void Mesh::loadObjectFile(const std::string& filePath)
{
	// Containers to store the positions, texcoords, and normals from the object file
	std::vector<vec3> vertex_positions;
	std::vector<vec2> vertex_texcoords;
	std::vector<vec3> vertex_normals;

	// Containers to store the face indices
	std::vector<unsigned int> vertex_position_indices;
	std::vector<unsigned int> vertex_texcoord_indices;
	std::vector<unsigned int> vertex_normal_indices;

	// Reserve some capacity, to avoid insane amount of copies once the vector needs to be re-allocated...
	vertex_positions.reserve(1000);
	vertex_texcoords.reserve(1000);
	vertex_normals.reserve(1000);

	vertex_position_indices.reserve(1000);
	vertex_texcoord_indices.reserve(1000);
	vertex_normal_indices.reserve(1000);

	// String utilities to parse the object file
	std::stringstream ss;
	std::ifstream in_file(filePath);
	std::string line = "";
	std::string prefix = "";

	// Temporary variables used when pushing data to containers
	vec3 position;
	vec2 texcoord;
	vec3 normal;
	unsigned int index = 0;

	// Check if file has opened successfully
	if (!in_file.is_open())
	{
		std::cerr << "ERROR: Could not open object file: " << filePath << "!" << std::endl;
		m_isModelLoaded = false;
	}

	// Read one line at a time
	while (std::getline(in_file, line))
	{
		// Get the prefix of the line
		ss.clear();
		ss.str(line);
		ss >> prefix;

		// Vertex position
		if (prefix == "v")
		{
			ss >> position.x >> position.y >> position.z;
			vertex_positions.push_back(position);
		}

		// Vertex texture coordinate
		else if (prefix == "vt")
		{
			ss >> texcoord.x >> texcoord.y;
			vertex_texcoords.push_back(texcoord);
		}

		// Vertex normal
		else if (prefix == "vn")
		{
			ss >> normal.x >> normal.y >> normal.z;
			vertex_normals.push_back(normal);
		}

		// Face
		else if (prefix == "f")
		{
			int counter = 0;
			while (ss >> index)
			{
				// Pushing indices into correct arrays
				if (counter == 0)
					vertex_position_indices.push_back(index);
				else if (counter == 1)
					vertex_texcoord_indices.push_back(index);
				else if (counter == 2)
					vertex_normal_indices.push_back(index);

				// Ignoring these characters
				if (ss.peek() == '/')
				{
					counter++;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					counter++;
					ss.ignore(1, ' ');
				}

				// Reset the counter
				if (counter > 2)
					counter = 0;
			}
		}
	}

	// Close the file after finished reading it
	in_file.close();

	// Build final mesh
	vertices.resize(vertex_position_indices.size(), vec3());
	uvs.resize(vertex_position_indices.size(), vec2());
	normals.resize(vertex_position_indices.size(), vec3());
	indices.resize(vertex_position_indices.size());
		
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i] = vertex_positions[vertex_position_indices[i] - 1];
		uvs[i] = vertex_texcoords[vertex_texcoord_indices[i] - 1];
		normals[i] = vertex_normals[vertex_normal_indices[i] - 1];
		indices[i] = i;
	}

}

