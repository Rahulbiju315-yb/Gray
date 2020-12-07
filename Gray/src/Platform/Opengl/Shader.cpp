#include "grpch.h"

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GL/glew.h"

#include "unordered_map"

namespace Gray
{

	unsigned int boundShaderID = 0;

	bool LoadShaderProgram(std::string& vertexSource, std::string& fragmentSource, const std::string& file)
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
			return false;
		}
		return true;
	}

	bool CompileShader(const std::string& vertexSource, const std::string& fragmentSource, unsigned int& ID)
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
			return false;
		}

		glCompileShader(fragmentID);
		glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
			std::cout << "Error compiling fragment shader source ... \n" << infoLog;
			return false;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertexID);
		glAttachShader(ID, fragmentID);
		glLinkProgram(ID);
		glGetShaderiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "Error linking program ... \n" << infoLog;
			return false;
		}

		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);

		return true;
	}


	Shader::Shader(const std::string& filePath)
	{
		ID = 0;

		std::string vertexSource, fragmentSource;
		bool a = LoadShaderProgram(vertexSource, fragmentSource, filePath);
		bool b = CompileShader(vertexSource, fragmentSource, ID);
		
		success = a & b;
		attatched = false;
	}

	void Shader::Bind() const
	{
		if (boundShaderID != ID)
		{
			glUseProgram(ID);
			boundShaderID = ID;
		}
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
		boundShaderID = 0;
	}

	void Shader::SetUniform(const std::string& name, int i) const 
	{
		Bind();
		glUniform1i(GetUniformLocation(name.c_str()), i);
	}

	void Shader::SetUniform(const std::string& name, float f) const
	{
		Bind();
		glUniform1f(GetUniformLocation(name.c_str()), f);
	}

	void Shader::SetUniform(const std::string& name, const glm::vec2& v2) const 
	{
		Bind();
		glUniform2f(GetUniformLocation(name.c_str()), v2.x, v2.y);
	}

	void Shader::SetUniform(const std::string& name, const glm::vec3& v3) const 
	{
		Bind();
		glUniform3f(GetUniformLocation(name.c_str()), v3.x, v3.y, v3.z);
	}

	void Shader::SetUniform(const std::string& name, const glm::vec4& v4) const
	{
		Bind();
		glUniform4f(GetUniformLocation(name.c_str()), v4.x, v4.y, v4.z, 1.0f);
	}

	void Shader::SetUniform(const std::string& name, const glm::mat4& m4) const
	{
		Bind();
		glUniformMatrix4fv(GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(m4));
	}

	bool Shader::IsLoadSucces()
	{
		return success;
	}

	void Shader::SetAttatched(bool attatched)
	{
		this->attatched = attatched;
	}

	bool Shader::IsAttatched()
	{
		return attatched;
	}

	int Shader::GetUniformLocation(const std::string& name) const
	{
		if(hashTable.find(name) != hashTable.end())
			return (hashTable.find(name))->second;
		else
			hashTable.insert({name, glGetUniformLocation(ID, name.c_str())});

		return (hashTable.find(name))->second;
	}
}