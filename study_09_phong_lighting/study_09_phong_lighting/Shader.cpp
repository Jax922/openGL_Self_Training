#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <type_traits>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

int compileShaders(int shaderType, const char* shaderSource);
void checkCompileErrors(unsigned int shader, std::string type);

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::ifstream vShaderFile, fShaderFile;
	std::string vertexCode, fragmentCode;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		m_vertexCode = vShaderStream.str();
		m_fragmentCode = fShaderStream.str();

	
		//m_ID = glCreateProgram();

	}
	catch (const std::exception& ex)
	{
		std::cout << "import shader source file error:====" << ex.what() << std::endl;
	}

}

void Shader::Build()
{
	unsigned int vertexShader;
	unsigned int fragmentShader;

	//vertexShader = compileShaders(GL_VERTEX_SHADER, m_vertexSource);
	//fragmentShader = compileShaders(GL_FRAGMENT_SHADER, m_fragmentSource);

	m_vertexSource = m_vertexCode.c_str();
	m_fragmentSource = m_fragmentCode.c_str();
	std::cout << m_vertexSource << std::endl;
	std::cout << m_fragmentSource << std::endl;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &m_vertexSource, NULL);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "VERTEX");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &m_fragmentSource, NULL);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, "FRAGMENT");


	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	glLinkProgram(m_ID);
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Use()
{
	glUseProgram(m_ID);
}

//template <typename T> // T can be one of : bool, int, float
void Shader::SetValue(std::string name, int value)
{
	//bool isInt = std::is_same<T, int>::value || std::is_same<T, bool>::value;
	//bool isFloat = std::is_same<T, float>::value;
	
	//if (isInt)
	//{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
	//}

	/*if (isFloat)
	{
		glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
	}*/
}

void Shader::SetValue(std::string name, glm::mat4 trans)
{
	unsigned int transform = glGetUniformLocation(m_ID, name.c_str());
	glUniformMatrix4fv(transform, 1, GL_FALSE, glm::value_ptr(trans));
}

void Shader::SetValue(std::string name, glm::vec3 vector)
{
	unsigned int locate = glGetUniformLocation(m_ID, name.c_str());
	glUniform3fv(locate, 1, glm::value_ptr(vector));
}



int compileShaders(int shaderType, const char* shaderSource)
{
	//int shader = shaderType == "vertex" ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
	std::cout << shaderSource << std::endl;
	int success;
	char infoLog[512];
	// complie shaders
	unsigned int shader;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILER::" << infoLog << std::endl;
		return -1;
	}

	return shader;
}

void checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
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
