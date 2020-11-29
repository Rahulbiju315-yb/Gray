#pragma once


#include <glm/glm.hpp>
#include "Gray/Core.h"
namespace Gray
{
	class Shader
	{

	public:
		Shader(const std::string& filePath);
		void Bind() const;
		void Unbind() const;

		void SetUniform(const std::string& name, int i);
		void SetUniform(const std::string& name, float f);

		void SetUniform(const std::string& name, const glm::vec2& v2);
		void SetUniform(const std::string& name, const glm::vec3& v3);
		void SetUniform(const std::string& name, const glm::vec4& v4);
		void SetUniform(const std::string& name, const glm::mat4& m4);

		bool IsLoadSucces();

		void SetAttatched(bool attatched);
		bool IsAttatched();
	private:
		static unsigned int boundShaderID;
		unsigned int ID;
		bool success;
		bool attatched;

		std::unordered_map <std::string, int> hashTable;
		int GetUniformLocation(const std::string& name);

	};
}