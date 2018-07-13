#pragma once
#define _CRT_SECURE_NO_DEPRECATE

#include "glew.h"
#include "maths.h"
#include <string.h>

class Shader {
public:
	GLuint ID;

	/* Initialize vertex and fragment shader. Read the files and compile them. Create shader program. */
	GLint init(const GLchar* vertex_shader_path, const GLchar* fragment_shader_path);

	/* Use this program */
	GLvoid use();

	/* Set uniform: bool */
	GLvoid setBool(std::string name, GLboolean value);

	/* Set uniform: int */
	GLvoid setInt(std::string name, GLint value);

	/* Set uniform: float */
	GLvoid setFloat(std::string name, GLfloat value);
	
	/* Set uniform: vec2 */
	GLvoid setVec2(std::string name, const vec2& value);
	
	/* Set uniform: vec3 */
	GLvoid setVec3(std::string name, const vec3& value);
	
	/* Set uniform: vec4 */
	GLvoid setVec4(std::string name, const vec4& value);

	/* Set uniform: mat2 */
	GLvoid setMat2(std::string, const mat2& mat);

	/* Set uniform: mat3 */
	GLvoid setMat3(std::string name, const mat3& mat);

	/* Set uniform: mat4 */
	GLvoid setMat4(std::string name, const mat4& mat);

private:
	GLchar vertex_path[256];
	GLchar fragment_path[256];

	/* Read from file specified and store in a string */
	static GLchar* readFile(const GLchar* file_path);
	
};