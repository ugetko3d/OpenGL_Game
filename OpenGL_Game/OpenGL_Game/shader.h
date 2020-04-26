#pragma once

class Shader
{
public:
	// Constructor
	Shader();

	Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

	// Desctructor
	~Shader();

	// Method to load shader from file
	void loadShader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

	// Use this program
	void use();

	// Set uniform: bool
	void setBool(const std::string& name, bool value) const;

	// Set uniform: int
	void setInt(const std::string& name, int value) const;

	// Set uniform: float
	void setFloat(const std::string& name, float value) const;

	// Set uniform: vec2
	void setVec2(const std::string& name, const vec2& value) const;

	// Set uniform: vec3
	void setVec3(const std::string& name, const vec3& value) const;

	// Set uniform: vec4
	void setVec4(const std::string& name, const vec4& value) const;

	// Set uniform: mat4
	void setMat4(const std::string& name, const mat4& mat) const;

private:
	unsigned int m_program;

	void parseFile(const std::string& file_path, std::string& shaderCode);
	unsigned int compileShader(unsigned int type, const std::string& source);
	void errorChecking(unsigned int shader, const std::string& type);
};