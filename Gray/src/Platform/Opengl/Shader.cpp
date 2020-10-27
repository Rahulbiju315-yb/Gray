#include "grpch.h"

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GL/glew.h"



std::unordered_map <std::string, int> hashTable;

namespace Gray
{
	void LoadShaderProgram(std::string& vertexSource, std::string& fragmentSource, const std::string& file)
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
		catch (std::ifstream::failure e)
		{
			std::cout << "Error reading file " << file;
			GRAY_CORE_ERROR("Error Reading shader file");
		}
	}

	void CompileShader(const std::string& vertexSource, const std::string& fragmentSource, unsigned int& ID)
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
		LoadShaderProgram(vertexSource, fragmentSource, filePath);
		CompileShader(vertexSource, fragmentSource, ID);

	}

	void Shader::Bind() const
	{
		glUseProgram(ID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetUniform(const std::string& name, int i) const
	{
		glUniform1i(GetUniformLocation(name.c_str()), i);
	}

	void Shader::SetUniform(const std::string& name, float f) const
	{
		glUniform1f(GetUniformLocation(name.c_str()), f);
	}

	void Shader::SetUniform(const std::string& name, const glm::vec2& v2) const
	{
		glUniform2f(GetUniformLocation(name.c_str()), v2.x, v2.y);
	}

	void Shader::SetUniform(const std::string& name, const glm::vec3& v3) const
	{
		glUniform3f(GetUniformLocation(name.c_str()), v3.x, v3.y, v3.z);
	}

	void Shader::SetUniform(const std::string& name, const glm::vec4& v4) const
	{
		glUniform4f(GetUniformLocation(name.c_str()), v4.x, v4.y, v4.z, 1.0f);
	}

	void Shader::SetUniform(const std::string& name, const glm::mat4& m4) const
	{
		glUniformMatrix4fv(GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(m4));
	}

	int Shader::GetUniformLocation(const std::string& name) const
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
}