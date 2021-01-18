#include "grpch.h"
#include "ResourceManager.h"

namespace Gray
{
	std::vector<NoCopy<Texture>> textures;
	std::vector<std::string> texturePaths;
	std::vector<Model> models;

	const Texture* GetTexture(const std::string& path, bool flipTextures)
	{
		GRAY_CORE_INFO("Attempting to load texture : " + path);
		const Texture* tex = nullptr;

		//Linear Search for path in paths
		for (int i = 0; i < texturePaths.size(); i++)
		{
			if (texturePaths[i] == path)
			{
				return textures[i].Get();
			}
		}

		//If Not found
		NoCopy<Texture> texture;

		uint formInternal, formExternal;

		if (texture->LoadTexture(path, flipTextures))
		{
			textures.push_back(std::move(texture));
			texturePaths.push_back(path);

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

	Model GetModel(std::string path, bool flipTexture)
	{
		for (Model& model : models)
			if (model.GetPath() == path)
				return model;

		models.push_back(Model());
		models.back().LoadModel(path, flipTexture);

		return models.back();
	}
}