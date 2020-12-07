#pragma once

#include "Platform/Opengl/Shader.h"
namespace Gray
{
	class UniformManager
	{
	public:
		virtual void SetUniformFor(const Shader& shader) const = 0;
	};
}