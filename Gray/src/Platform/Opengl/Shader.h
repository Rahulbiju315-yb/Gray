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

		void SetUniform(const std::string& name, int i) const;
		void SetUniform(const std::string& name, float f) const;

		void SetUniform(const std::string& name, const glm::vec2& v2) const;
		void SetUniform(const std::string& name, const glm::vec3& v3) const;
		void SetUniform(const std::string& name, const glm::vec4& v4) const;
		void SetUniform(const std::string& name, const glm::mat4& m4) const;

		bool IsLoadSucces();

		void SetAttatched(bool attatched);
		bool IsAttatched();
	private:
		unsigned int ID;
		bool success;
		bool attatched;

		mutable std::unordered_map <std::string, int> hashTable;
		int GetUniformLocation(const std::string& name) const;

	};
}