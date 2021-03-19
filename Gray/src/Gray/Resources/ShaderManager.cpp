#include "grpch.h"
#include "ShaderManager.h"

namespace Gray
{

	WeakRef<Shader> ShaderManager::GetShader(const std::string& sp)
	{
		for (int i = 0; i < paths.size(); i++)
		{
			if (paths[i] == sp)
				return WeakRef<Shader>(shaders[i]);
		}

		// If not found
		shaders.emplace_back();
		paths.push_back(sp);
		shaders.back()->LoadProgram(sp);

		return WeakRef<Shader>(shaders.back());
	}
}