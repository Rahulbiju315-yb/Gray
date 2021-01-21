#include "grpch.h"
#include "ResourceManager.h"

#include "Platform/Opengl/Shader.h"

namespace Gray
{
	std::vector<Shared<Shader>> shaders;
	std::vector<std::string> paths;
	Shared<Shader> RMGetShader(const std::string& path)
	{
		//Linear Search for path in paths
		for (int i = 0; i < paths.size(); i++)
		{
			if (paths[i] == path)
			{
				return shaders[i];
			}
		}

		//If Not found
		Shared<Shader> shader;
		shader->LoadProgram(path);
		shaders.push_back(shader);
		paths.push_back(path);

		return shaders.back();
		
	}

	void RMReloadShaders()
	{
		//Linear Search for path in paths
		for (int i = 0; i < paths.size(); i++)
		{
			shaders[i] = Shared<Shader>();
			shaders[i]->LoadProgram(paths[i]);
		}

	}
	
}