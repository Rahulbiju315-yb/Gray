#include "grpch.h"
#include "ResourceManager.h"
#include "GLFW/glfw3.h"
#include "Gray/Window/Window.h"
#include "Platform/Opengl/stb_image.h"
#include "Gray/Image/Image.h"

namespace Gray
{

	std::vector<NoCopy<Texture>> textures;
	std::vector<std::string> texturePaths;

	std::vector<WeakRef<Texture>>  llTextures;
	std::vector<Image> imData;

	bool isExec = false;
	int loadIndex = 0;

	WeakRef<Texture> GetTexture(const std::string& path)
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
		Image image;
		image.path = path;
		imData.push_back(image);

		if (loadIndex == -1)
			loadIndex = 0;

		return WeakRef<Texture>(textures.back());
	}

	void LoadTextureJob(Image& image) 
	{ 
		LoadImage(image);
		loadIndex++;
		isExec = false;
	}

	// returns true if all image files have been read
	bool ImageLoadDone()
	{
		if (isExec)
			return false;

		if (imLoadThread.joinable())
			imLoadThread.join();

		if (loadIndex < 0)
			return true;

		// All images in To-Load-images list has been loaded.
		// Load the data to corresponding textures.
		if (loadIndex == imData.size())
		{
			for (int i = 0; i < imData.size(); i++)
			{
				Image& im = imData[i];
				if(im.data)
					llTextures[i]->LoadTextureFrom(im);
			}

			imData.clear();
			llTextures.clear();
			loadIndex = -1;
			return true;
		}
		
		// The previous image loading has finished. Load the next one in the list.
		Image& im = imData[loadIndex];
		isExec = true;
		imLoadThread = std::thread(LoadTextureJob, std::ref(im));

		return false;
	}

	void FinishTextureLoad()
	{
		if (imLoadThread.joinable())
			imLoadThread.join();
	}

	void ClearImageLoadList()
	{
		FinishTextureLoad();
		llTextures.clear();
		imData.clear();
	}

	Material CreateMaterial()
	{
		static uint ID = 0;

		Material m;
		m.ID = ID++;

		return m;
	}

	
}