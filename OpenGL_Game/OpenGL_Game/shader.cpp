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
	// Parsing Shader Code
	std::string vertexCode, fragmentCode;

	std::cout << "Parsing Vertex Shader code..." << std::endl;
	parseFile(vertex_shader_path, vertexCode);

	std::cout << "Parsing Fragment Shader code..." << std::endl;
	parseFile(fragment_shader_path, fragmentCode);

	// Compile the shaders
	std::cout << "Compiling: Vertex Shader" << std::endl;
	GLuint vs = compileShader(GL_VERTEX_SHADER, vertexCode);

	std::cout << "Compiling: Fragment Shader" << std::endl;
	GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

	// Print compile errors if any
	std::cout << "Checking for errors in Vertex Shader compilation..." << std::endl;
	errorChecking(vs, "VERTEX");

	std::cout << "Checking for errors in Fragment Shader compilation..." << std::endl;
	errorChecking(fs, "FRAGMENT");

	// Link vertex shader and fragment shader
	std::cout << "Linking: " << vertex_shader_path << " and " << fragment_shader_path << std::endl;
	m_program = glCreateProgram();
	glAttachShader(m_program, vs);
	glAttachShader(m_program, fs);
	glLinkProgram(m_program);

	// Print linking errors if any
	std::cout << "Checking for errors in Program linking..." << std::endl;
	errorChecking(m_program, "PROGRAM");

	// Delete the shaders as they're linked into our program now and are no longer necessery
	glDeleteShader(vs);
	glDeleteShader(fs);
}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

void Shader::use()
{
	glUseProgram(m_program);
}

void Shader::setBool(const std::string& name, GLboolean value) const
{
	glUniform1i(glGetUniformLocation(m_program, name.c_str()), (GLint) value);
}

void Shader::setInt(const std::string& name, GLint value) const
{
	glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, GLfloat value) const
{
	glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const vec2& value) const
{
	float temp[] = { value.x, value.y };
	glUniform2fv(glGetUniformLocation(m_program, name.c_str()), 1, temp);
}

void Shader::setVec3(const std::string& name, const vec3& value) const
{
	float temp[] = { value.x, value.y, value.z };
	glUniform3fv(glGetUniformLocation(m_program, name.c_str()), 1, temp);
}

void Shader::setVec4(const std::string& name, const vec4& value) const
{
	float temp[] = { value.x, value.y, value.z, value.w };
	glUniform4fv(glGetUniformLocation(m_program, name.c_str()), 1, temp);
}

void Shader::setMat2(const std::string& name, const mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, mat.data);
}

void Shader::setMat3(const std::string& name, const mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, mat.data);
}

void Shader::setMat4(const std::string& name, const mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, mat.data);
}


GLvoid Shader::parseFile(const std::string& file_path, std::string& shaderCode)
{
	// Retrieve the vertex / fragment source code from the file paths
	std::ifstream shaderFile;

	// Ensure ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// Open file
		shaderFile.open(file_path);

		std::stringstream shaderStream;

		// Read file's buffer contents into stream
		shaderStream << shaderFile.rdbuf();

		// Close file handler
		shaderFile.close();

		// Convert stream into string
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
}

GLuint Shader::compileShader(GLuint type, const std::string& source)
{
	GLuint id = glCreateShader(type);

	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	return id;
}

GLvoid Shader::errorChecking(GLuint id, const std::string& type)
{
	GLint success;
	char* message;
	GLint length;

	if (type != "PROGRAM")
	{
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			message = new char[length];
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << message << "\n -- --------------------------------------------------- -- " << std::endl;
			delete[] message;
			glDeleteShader(id);
		}
	}
	else
	{
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
			message = new char[length];
			glGetProgramInfoLog(id, length, &length, message);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << message << "\n -- --------------------------------------------------- -- " << std::endl;
			delete[] message;
			glDeleteProgram(id);
		}
	}
}