#include "core/shader.hpp"

using namespace gui;

char Shader::infoLog[512];
Shader *Shader::current;

static char* readFile(const char *fileName)
{
	FILE *file; 
	long size;
	char *text;

	file = fopen(fileName, "rb");
	fseek(file, 0L, SEEK_END);
	size = ftell(file);
	text = new char[size + 1];
	text[size] = '\0';
	fseek(file, 0L, SEEK_SET);
	fread(text, 1, size, file);
	fclose(file);
	return text;
}

static GLuint compileShader(GLenum type, const char *source)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {

		glGetShaderInfoLog(shader, 512, nullptr, Shader::infoLog);
		fmt::println("Shader compilation error:\n{}", Shader::infoLog);
	}
	return shader;
}

Shader::Shader(const char *vertexShader, const char *fragmentShader)
{
	char *vertexCode = readFile(vertexShader);
	char *fragmentCode = readFile(fragmentShader);

	GLuint vertex = compileShader(GL_VERTEX_SHADER, vertexCode);
	GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		
		glGetProgramInfoLog(program, 512, nullptr, Shader::infoLog);
		fmt::println("Shader linking error:\n{}", Shader::infoLog);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	delete[] vertexCode;
	delete[] fragmentCode;
}

Shader::~Shader()
{
	glDeleteProgram(program);
}

void Shader::use()
{
	if (Shader::current != this) {

		Shader::current = this;
		glUseProgram(program);
	}
}
