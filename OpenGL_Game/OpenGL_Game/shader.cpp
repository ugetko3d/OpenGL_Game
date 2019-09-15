#include <glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "maths.h"
#include "shader.h"
#include "texture.h"
 
Shader::Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{
	// Retrieve the vertex / fragment source code from the file paths
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;

	// Ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// Open files
		vShaderFile.open(vertex_shader_path);
		fShaderFile.open(fragment_shader_path);

		std::stringstream vShaderStream, fShaderStream;

		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// Close file handlers
		vShaderFile.close();
		fShaderFile.close();

		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		std::cout << vertexCode << std::endl;
		std::cout << fragmentCode << std::endl;

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vertex_source = vertexCode.c_str();
	const char* fragment_source = fragmentCode.c_str();

	uint32_t vertexID, fragmentID;

	// Compile the vertex shader
	std::cout << "Compiling: " << vertex_shader_path << std::endl;
	vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vertex_source, NULL);
	glCompileShader(vertexID);

	// Print compile errors if any
	checkCompileErrors(vertexID, "VERTEX");

	// Compile the fragment shader
	std::cout << "Compiling: " << fragment_shader_path << std::endl;
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fragment_source, NULL);
	glCompileShader(fragmentID);

	// Print compile errors if any
	checkCompileErrors(fragmentID, "FRAGMENT");

	// Link vertex shader and fragment shader
	std::cout << "Linking: " << vertex_shader_path << " and " << fragment_shader_path << std::endl;
	ID = glCreateProgram();
	glAttachShader(ID, vertexID);
	glAttachShader(ID, fragmentID);
	glLinkProgram(ID);

	// Print linking errors if any
	checkCompileErrors(ID, "PROGRAM");

	// Delete the shaders as they're linked into our program now and are no longer necessery
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

GLvoid Shader::checkCompileErrors(uint32_t shader, const std::string& type)
{
	int32_t success;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, GLboolean value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (GLint) value);
}

void Shader::setInt(const std::string& name, GLint value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, GLfloat value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const vec2& value) const
{
	float temp[] = { value.x, value.y };
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, temp);
}

void Shader::setVec3(const std::string& name, const vec3& value) const
{
	float temp[] = { value.x, value.y, value.z };
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, temp);
}

void Shader::setVec4(const std::string& name, const vec4& value) const
{
	float temp[] = { value.x, value.y, value.z, value.w };
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, temp);
}

void Shader::setMat2(const std::string& name, const mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat.data);
}

void Shader::setMat3(const std::string& name, const mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat.data);
}

void Shader::setMat4(const std::string& name, const mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat.data);
}