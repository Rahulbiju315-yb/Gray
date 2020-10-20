#pragma once


#include <glm/glm.hpp>

namespace Gray
{
	class Shader
	{
	private:
		unsigned int ID;

		int getUniformLocation(const std::string& name) const;

	public:
		Shader(const std::string& filePath);
		void bind() const;
		void unbind() const;

		void setUniform(const std::string& name, int i) const;
		void setUniform(const std::string& name, float f) const;

		void setUniform(const std::string& name, const glm::vec2& v2) const;
		void setUniform(const std::string& name, const glm::vec3& v3) const;
		void setUniform(const std::string& name, const glm::vec4& v4) const;
		void setUniform(const std::string& name, const glm::mat4& m4) const;

	};
}