#pragma once

#include "Platform/Opengl/Texture.h"
#include "Materials.h"

namespace Gray
{
	std::vector<NoCopy<Texture>> textures;
	std::vector<std::string> paths;
	const Texture* GetTexture(const std::string& path, bool flipTextures=true)
	{
		GRAY_CORE_INFO("Attempting to load texture : " + path);
		const Texture* tex = nullptr;

		//Linear Search for path in paths
		for (int i = 0; i < paths.size(); i++)
		{
			if (paths[i] == path)
			{
				return textures[i].Get();
			}
		}

		//If Not found
		NoCopy<Texture> texture;
		if (texture->LoadTexture(path, flipTextures, GL_COMPRESSED_RGBA, GL_RGBA))
		{
			textures.push_back(std::move(texture));
			paths.push_back(path);

			return textures.back().Get();
		}
		else
		{
			return Defaults::BlankTex();
		}
		
	}

	Material CreateMaterial()
	{
		static uint ID = 0;

		Material m;
		m.ID = ID++;

		return m;
	}
}