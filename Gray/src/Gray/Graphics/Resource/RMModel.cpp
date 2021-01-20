#include "grpch.h"
#include "ResourceManager.h"

namespace Gray
{
	
	
	std::vector<Model> models;
	Model GetModel(std::string path, bool flipTexture)
	{
		for (Model& model : models)
			if (model.GetPath() == path)
				return model;

		models.push_back(Model());
		models.back().LoadModel(path, flipTexture);

		return models.back();
	}

	void ReloadModel(const std::string& path, bool flipTexture)
	{
		for (int i = 0; i < models.size(); i++)
		{
			if (models[i].GetPath() == path)
			{
				models[i].LoadModel(path, flipTexture);
				return;
			}
		}
	}

}