#pragma once

#include "Platform/Opengl/Texture.h"
#include "Platform/Opengl/Shader.h"
#include "Gray/Graphics/Materials.h"
#include "Gray/Graphics/Model/Model.h"


namespace Gray
{
	std::thread modelLoadThread;
	std::thread imLoadThread;

	const std::string DEFAULT_SHADER = "res/models/shaders/shader.shader";

	void AddModelFileForImport(const std::string& path);
	bool TryLoadModel(Model& m);
	void FinishModelLoad();
	void ClearModelLoadList();
	bool IsModelLoaded(const std::string& path);
	Model GetModel(const std::string& path);


	Shared<Shader> RMGetShader(const std::string& path);
	void RMReloadShaders();

	WeakRef<Texture> GetTexture(const std::string& path);
	bool ImageLoadDone();
	void FinishTextureLoad();

	Material CreateMaterial();

}