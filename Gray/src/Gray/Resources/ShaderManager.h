#pragma once

#include "Platform/Opengl/Shader.h"

namespace Gray
{
	class ShaderManager
	{
	public:
		ShaderManager() = default;
		WeakRef<Shader> GetShader(const std::string& sp);

	private:
		std::vector<NoCopy<Shader>> shaders;
		std::vector<std::string> paths;
	};
}