#pragma once

class Shader {
public:
	// Constructor
	Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

	~Shader();

	// Use this program
	GLvoid use();

	// Set uniform: bool
	GLvoid setBool(const std::string& name, GLboolean value) const;

	// Set uniform: int
	GLvoid setInt(const std::string& name, GLint value) const;

	// Set uniform: float
	GLvoid setFloat(const std::string& name, GLfloat value) const;
	
	// Set uniform: vec2
	GLvoid setVec2(const std::string& name, const vec2& value) const;
	
	// Set uniform: vec3
	GLvoid setVec3(const std::string& name, const vec3& value) const;
	
	// Set uniform: vec4
	GLvoid setVec4(const std::string& name, const vec4& value) const;

	// Set uniform: mat4
	GLvoid setMat4(const std::string& name, const mat4& mat) const;

private:
	GLuint m_program;

	GLvoid parseFile(const std::string& file_path, std::string& shaderCode);
	GLuint compileShader(GLuint type, const std::string& source);
	GLvoid errorChecking(GLuint shader, const std::string& type);
};