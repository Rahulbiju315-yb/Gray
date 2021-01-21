#include "grpch.h"
#include "ResourceManager.h"
#include <assimp/cimport.h>

namespace Gray
{
	
	std::vector<Model> models;
	std::vector<std::string> modelFilePaths;

	const aiScene* loadedScene;

	bool model_isExec = false;
	int modelLoadIndex = -1;

	std::thread modelLoadThread;

	bool IsModelLoaded(const std::string& path)
	{
		for (int i = 0; i < models.size(); i++)
		{
			if (models[i].GetPath() == path)
				return true;
		}
		return false;
	}

	Model GetModel(const std::string& path)
	{
		for (int i = 0; i < models.size(); i++)
		{
			if (models[i].GetPath() == path)
				return models[i];
		}

		return Model();
	}

	void ImportScene(std::string path)
	{
		loadedScene = aiImportFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

		if (loadedScene == nullptr)
			GRAY_CORE_ERROR("Error Reading Model File " + path);
		else
			GRAY_CORE_INFO("Succesfully loaded model" + path);
		modelLoadIndex++;
		model_isExec = false;
	}

	void AddModelFileForImport(const std::string& path)
	{
		modelFilePaths.push_back(path);
		if (modelLoadIndex == -1)
			modelLoadIndex = 0;
	}

	// tries loading the given model m with the scene that has been loaded.
	// returns true if success.
	bool TryLoadSceneForModel(Model& m)
	{
		if (model_isExec)
			return false;

		if (modelLoadIndex == -1)
			return false;

		if (modelLoadThread.joinable())
			modelLoadThread.join();

		bool ret = false;
		if (loadedScene)
		{
			assert(modelLoadIndex >= 1);
			assert(m.GetPath() == modelFilePaths[(size_t)modelLoadIndex - 1]);
			assert(modelLoadIndex >= 0);
			assert(loadedScene != nullptr && "loaded scene null in TryLoadScene");
			m.LoadScene(loadedScene);
			aiReleaseImport(loadedScene);
			loadedScene = nullptr;
			models.push_back(m);
			ret = true;
		}
		
		if (modelLoadIndex == modelFilePaths.size())
		{
			modelLoadIndex = -1;
			modelFilePaths.clear();
			return ret;
		}

		assert(modelLoadIndex < modelFilePaths.size());

		model_isExec = true;
		modelLoadThread = std::thread(ImportScene, modelFilePaths[modelLoadIndex]);
		return ret;
	}

	bool IsModelPathsEmpty()
	{
		return !modelLoadThread.joinable();
	}
}