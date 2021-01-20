#include "grpch.h"
#include "ResourceManager.h"
#include "GLFW/glfw3.h"
#include "Gray/Window/Window.h"
#include "Platform/Opengl/stb_image.h"


namespace Gray
{

	std::vector<NoCopy<Texture>> textures;
	std::vector<std::string> texturePaths;

	std::vector<WeakRef<Texture>>  llTextures;
	std::vector<Image> imData;

	std::thread imLoadThread;
	bool isExec = false;
	int loadIndex = 0;

	WeakRef<Texture> GetTextureParallel(const std::string& path)
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
		texture->LoadEmptyTexture(1, 1);
		textures.push_back(std::move(texture));
		texturePaths.push_back(path);
		
		llTextures.push_back(WeakRef<Texture>(textures.back()));
		Image image{ nullptr, path, 0, 0 };
		imData.push_back(image);

		if (loadIndex == -1)
			loadIndex = 0;

		return llTextures.back();
	}

	WeakRef<Texture> GetTexture(const std::string& path, bool flipTextures)
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
		if (texture->LoadTexture(path, true))
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

	void Load(Image& image) 
	{ 
		image.data = stbi_load(image.path.c_str(), &(image.width), &(image.height), 
			&image.nrChannels, STBI_rgb_alpha);
		loadIndex++;
		isExec = false;
	}

	// returns true is thread is running
	bool LoadTexIfFree()
	{
		if (isExec)
			return false;

		if (imLoadThread.joinable())
			imLoadThread.join();

		// All images in To-Load-images list has been loaded.
		// Load the data to corresponding textures.
		if (loadIndex == imData.size())
		{
			for (int i = 0; i < imData.size(); i++)
			{
				Image& im = imData[i];
				llTextures[i]->LoadTextureFrom(im.data, im.width, im.height, im.nrChannels);
				stbi_image_free(im.data);
			}

			imData.clear();
			llTextures.clear();
			loadIndex = -1;
			return true;
		}
		
		if (loadIndex < 0)
			return true;

		// The previous image loading has finished. Load the next one in the list.
		Image& im = imData[loadIndex];
		isExec = true;
		imLoadThread = std::thread(Load, std::ref(im));
		llTextures[loadIndex]->LoadTextureFrom(im.data, im.width, im.height, im.nrChannels);

		return false;
	}

	Material CreateMaterial()
	{
		static uint ID = 0;

		Material m;
		m.ID = ID++;

		return m;
	}

}