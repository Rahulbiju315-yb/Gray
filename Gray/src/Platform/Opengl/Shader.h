#pragma once

#include "glm/glm.hpp"
#include "Shared.h"
#include "NoCopy.h"
#include "WeakRef.h"

namespace Gray
{
	class Shader
	{

	public:
		void Bind() const;
		void Unbind() const;
		bool IsBound() const;

		bool LoadProgram(const std::string& filePath);

		void SetUniform(const std::string& name, int i) const;
		void SetUniform(const std::string& name, float f) const;

		void SetUniform(const std::string& name, const glm::vec2& v2) const;
		void SetUniform(const std::string& name, const glm::vec3& v3) const;
		void SetUniform(const std::string& name, const glm::vec4& v4) const;
		void SetUniform(const std::string& name, const glm::mat4& m4) const;
		void SetUniform(const std::string& name, const glm::mat3& m3) const;

		bool IsLoadSucces() const;

		uint GetID() const;

	private:

		uint ID;
		static uint boundShader_ID;
		mutable bool success;

		Shader();
		Shader(const std::string& filePath);

		Shader(const Shader&) = default;
		Shader(Shader&&) = default;

		Shader& operator=(const Shader&) = default;
		Shader& operator=(Shader&&) = default;

		void CopyFrom(const Shader&);
		void CreateIfEmpty();
		void Free();

		mutable std::unordered_map <std::string, int> hashTable;
		int GetUniformLocation(const std::string& name) const;

		friend class NoCopy<Shader>;
		friend class Shared<Shader>;
		friend class WeakRef<Shader>;
	};

	bool LoadShaderSource(std::string& vertexSource, std::string& fragmentSource, const std::string& file);
	bool CompileShader(const std::string& vertexSource, const std::string& fragmentSource, const uint& ID);
}