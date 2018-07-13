#include "shader.h"
 
GLchar* Shader::readFile(const GLchar* file_path)
{
	GLchar* file_contents;
	GLint64 input_file_size;

	FILE* input_file = fopen(file_path, "rb");
	if (input_file == NULL) {
		printf("Error: Unable to open file: %s\n", file_path);
		return NULL;
	}
	fseek(input_file, 0, SEEK_END);
	input_file_size = ftell(input_file);
	rewind(input_file);
	file_contents = (GLchar*) malloc((input_file_size + 1) * (sizeof(GLchar)));
	fread(file_contents, sizeof(GLchar), input_file_size, input_file);
	fclose(input_file);
	file_contents[input_file_size] = 0;

	return file_contents;
}

GLint Shader::init(const GLchar* vertex_shader_path, const GLchar* fragment_shader_path)
{
	GLint success;
	GLchar infoLog[512];
	GLchar* vertex_source = readFile(vertex_shader_path);
	GLchar* fragment_source = readFile(fragment_shader_path);

	if (vertex_source == NULL) {
		printf("Error: Vertex Shader is empty\n", vertex_shader_path);
		return -1;
	}

	if (fragment_source == NULL) {
		printf("Error: Fragment Shader is empty\n", vertex_shader_path);
		return -1;
	}

	strcpy(vertex_path, vertex_shader_path);
	strcpy(fragment_path, fragment_shader_path);

	// Compile the vertex shader
	printf("Compiling: %s\n", vertex_shader_path);
	GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vertex_source, NULL);
	glCompileShader(vertexID);
	// Print compile errors if any
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
		std::cout << "Error: Vertex compilation failed!\n" << infoLog << std::endl;
		return -1;
	};
	// Compile the fragment shader
	printf("Compiling: %s\n", fragment_shader_path);
	GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fragment_source, NULL);
	glCompileShader(fragmentID);
	// Print compile errors if any
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
		std::cout << "Error: Fragment compilation failed!\n" << infoLog << std::endl;
		return -1;
	};
	// Link vertex shader and fragment shader
	printf("Linking: %s and %s\n", vertex_shader_path, fragment_shader_path);
	ID = glCreateProgram();
	glAttachShader(ID, vertexID);
	glAttachShader(ID, fragmentID);
	glLinkProgram(ID);
	// print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Error: Shader linking failed!\n" << infoLog << std::endl;
		return -1;
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	return 0;
}

GLvoid Shader::use()
{
	glUseProgram(ID);
}

GLvoid Shader::setBool(std::string name, GLboolean value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (GLint) value);
}

GLvoid Shader::setInt(std::string name, GLint value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

GLvoid Shader::setFloat(std::string name, GLfloat value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

GLvoid Shader::setVec2(std::string name, const vec2& value)
{
	GLfloat temp[] = { value.x, value.y };
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, temp);
}

GLvoid Shader::setVec3(std::string name, const vec3& value)
{
	GLfloat temp[] = { value.x, value.y, value.z };
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, temp);
}

GLvoid Shader::setVec4(std::string name, const vec4& value)
{
	GLfloat temp[] = { value.x, value.y, value.z, value.w };
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, temp);
}

GLvoid Shader::setMat2(std::string name, const mat2& mat)
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat.matrix);
}

GLvoid Shader::setMat3(std::string name, const mat3& mat)
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat.matrix);
}

GLvoid Shader::setMat4(std::string name, const mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat.matrix);
}