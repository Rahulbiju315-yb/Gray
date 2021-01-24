#include "grpch.h"

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GL/glew.h"

#include "unordered_map"

namespace Gray
{
	uint Shader::boundShader_ID = 0;

	
	Shader::Shader() : ID(0), success(false)
	{
	}

	Shader::Shader(const std::string& filePath) : Shader()
	{
		LoadProgram(filePath);
	}

	bool Shader::LoadProgram(const std::string& filePath)
	{
		CreateIfEmpty();

		std::string vertexSource, fragmentSource, geometrySource;
		bool a = LoadShaderSource(vertexSource, fragmentSource, geometrySource, filePath);
		assert(vertexSource.length() != 0);
		assert(fragmentSource.length() != 0);
		bool b = CompileShader(vertexSource, fragmentSource, geometrySource, ID);
		
		return a & b;
	}

	bool LoadShaderSource(std::string& vertexSource, std::string& fragmentSource, std::string& geometrySource,
		const std::string& file)
	{
		std::ifstream shaderFile;

		try
		{
			shaderFile.open(file.c_str());

			std::stringstream contents;
			contents << shaderFile.rdbuf();

			std::string s_contents = contents.str();

			std::string vertex, fragment, geometry;

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

			while (s_contents[i] != '\0' && s_contents[i] != '~')
			{
				fragment += s_contents[i++];
			}

			if (s_contents[i] == '~')
			{
				while (s_contents[i++] != '\n');

				while(s_contents[i] != '\0')
					geometry += s_contents[i++];
			}
			else
			{
				geometry = "";
			}

			vertexSource = vertex;
			fragmentSource = fragment;
			geometrySource = geometry;

			shaderFile.close();

		}
		catch (std::ifstream::failure e)
		{
			std::cout << "Error reading file " << file;
			GRAY_CORE_ERROR("Error Reading shader file");
			return false;
		}
		return true;
	}

	bool CompileShader(const std::string& vertexSource, const std::string& fragmentSource, 
		const std::string& geometrySource, const uint& ID)
	{
		const char* vsource = vertexSource.c_str();
		const char* fsource = fragmentSource.c_str();
		const char* gsource = geometrySource.c_str();

		char infoLog[512]; int success;

		//Compile and attach VertexShader
		int vertexID;
		vertexID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexID, 1, &vsource, NULL);

		glCompileShader(vertexID);
		glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
			std::cout << "Error compiling vertex shader source ... \n" << infoLog;
			return false;
		}

		glAttachShader(ID, vertexID);
		glDeleteShader(vertexID);

		//Compile And attach Fragment Shader
		int fragmentID;
		fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentID, 1, &fsource, NULL);

		glCompileShader(fragmentID);
		glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
			std::cout << "Error compiling fragment shader source ... \n" << infoLog;
			return false;
		}

		glAttachShader(ID, fragmentID);
		glDeleteShader(fragmentID);


		//If geometry shader is defined compile and attach that too
		if (geometrySource.size() != 0)
		{
			int geometryID;
			geometryID = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometryID, 1, &gsource, NULL);

			glCompileShader(geometryID);
			glGetShaderiv(geometryID, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(geometryID, 512, NULL, infoLog);
				std::cout << "Error compiling geometry shader source ... \n" << infoLog;
				return false;
			}

			glAttachShader(ID, geometryID);
			glDeleteShader(geometryID);
		}

		glLinkProgram(ID);
		glGetShaderiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "Error linking program ... \n" << infoLog;
			return false;
		}

		return true;
	}

	void Shader::CopyFrom(const Shader& shader)
	{
		ID = shader.ID;
		success = shader.success;
		hashTable = shader.hashTable;
	}

	void Shader::CreateIfEmpty()
	{
		if(ID == 0)
			ID = glCreateProgram();
	}

	void Shader::Free()
	{
		glDeleteProgram(ID);
	}

	void Shader::Bind() const
	{
		if (boundShader_ID != ID)
		{
			glUseProgram(ID);
			boundShader_ID = ID;
		}
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
		boundShader_ID = 0;
	}

	bool Shader::IsBound() const
	{
		return ID == boundShader_ID;
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

	void Shader::SetUniform(const std::string& name, const glm::mat3& m3) const
	{
		Bind();
		glUniformMatrix3fv(GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(m3));
	}

	bool Shader::IsLoadSucces() const
	{
		return success;
	}

	uint Shader::GetID() const
	{
		return ID;
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