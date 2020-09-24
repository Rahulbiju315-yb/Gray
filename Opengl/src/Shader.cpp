#include <Shader.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

std::unordered_map <std::string, int> hashTable;

void loadShaderProgram(std::string& vertexSource, std::string& fragmentSource, const std::string& file)
{
	std::ifstream shaderFile;

	try
	{
		shaderFile.open(file.c_str());

		std::stringstream contents;
		contents << shaderFile.rdbuf();

		std::string s_contents = contents.str();

		std::string vertex, fragment;

		int i = 0;
		
		if (s_contents[i] == '~')
		{
			while (s_contents[i++] != '\n');
		}

		while (s_contents[i] != '~')
		{
			vertex += s_contents[i++];
		}

		while (s_contents[i++] != '\n');
		
		while (s_contents[i] != '\0')
		{
			fragment += s_contents[i++];
		}

		vertexSource = vertex;
		fragmentSource = fragment;

	}
	catch(std::ifstream::failure e)
	{
		std::cout << "Error reading file " << file;
	}
}

void compileShader(const std::string& vertexSource, const std::string& fragmentSource, unsigned int& ID)
{
	const char* vsource = vertexSource.c_str();
	const char* fsource = fragmentSource.c_str();
	char infoLog[512]; int success;

	int vertexID;
	vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vsource, NULL);

	int fragmentID;
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fsource, NULL);

	glCompileShader(vertexID);
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
		std::cout << "Error compiling vertex shader source ... \n" << infoLog;
	}

	glCompileShader(fragmentID);
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
		std::cout << "Error compiling vertex shader source ... \n" << infoLog;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertexID);
	glAttachShader(ID, fragmentID);
	glLinkProgram(ID);
	glGetShaderiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Error compiling vertex shader source ... \n" << infoLog;
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

}

Shader::Shader(const std::string& filePath)
{
	ID = 0;

	std::string vertexSource, fragmentSource;
	loadShaderProgram(vertexSource, fragmentSource, filePath);
	compileShader(vertexSource, fragmentSource, ID);

}

void Shader::bind() const
{
	glUseProgram(ID);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::setUniform(const std::string& name, int i) const
{
	glUniform1i(getUniformLocation(name.c_str()), i);
}

void Shader::setUniform(const std::string& name, float f) const
{
	glUniform1f(getUniformLocation(name.c_str()), f);
}

void Shader::setUniform(const std::string& name, const glm::vec2& v2) const
{
	glUniform2f(getUniformLocation(name.c_str()), v2.x, v2.y);
}

void Shader::setUniform(const std::string& name, const glm::vec3& v3) const
{
	glUniform3f(getUniformLocation(name.c_str()), v3.x, v3.y, v3.z);
}

void Shader::setUniform(const std::string& name, const glm::vec4& v4) const
{
	glUniform4f(getUniformLocation(name.c_str()), v4.x, v4.y, v4.z, 1.0f);
}

void Shader::setUniform(const std::string& name, const glm::mat4& m4) const
{
	glUniformMatrix4fv(getUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(m4));
}

int Shader::getUniformLocation(const std::string& name) const
{
	int val;
	if (hashTable.find(name) == hashTable.end())
	{
		hashTable[name] = glGetUniformLocation(ID, name.c_str());
		return hashTable[name];
	}
	else
	{
		return hashTable[name];
	}
}