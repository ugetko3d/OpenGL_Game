#pragma once

class Shader {
public:
	GLuint ID;

	// Constructor
	Shader(const GLchar* vertex_shader_path, const GLchar* fragment_shader_path);

	// Use this program
	GLvoid use();

	// Set uniform: bool
	GLvoid setBool(std::string name, GLboolean value) const;

	// Set uniform: int
	GLvoid setInt(std::string name, GLint value) const;

	// Set uniform: float
	GLvoid setFloat(std::string name, GLfloat value) const;
	
	// Set uniform: vec2
	GLvoid setVec2(std::string name, const vec2& value) const;
	
	// Set uniform: vec3
	GLvoid setVec3(std::string name, const vec3& value) const;
	
	// Set uniform: vec4
	GLvoid setVec4(std::string name, const vec4& value) const;

	// Set uniform: mat2
	GLvoid setMat2(std::string, const mat2& mat) const;

	// Set uniform: mat3
	GLvoid setMat3(std::string name, const mat3& mat) const;

	// Set uniform: mat4
	GLvoid setMat4(std::string name, const mat4& mat) const;

private:
	GLvoid checkCompileErrors(GLuint shader, std::string type);

};