#pragma once

#include "Platform/Opengl/Texture.h"
#include "Platform/Opengl/Shader.h"
#include "Gray/Graphics/Materials.h"
#include "Gray/Graphics/Model/Model.h"


namespace Gray
{
	const std::string DEFAULT_SHADER = "res/models/shaders/shader.shader";

	void FinishAllLoads();

	// Model Manager
	void RM_AddModelFileForImport(const std::string& path);
	bool RM_TryLoadModel(Model& m);
	void RM_FinishModelLoad();
	void RM_ClearModelLoadList();
	bool RM_IsModelLoaded(const std::string& path);
	Model RM_GetModel(const std::string& path);

	// Shader manager
	Shared<Shader> RM_GetShader(const std::string& path);
	void RM_ReloadShaders();

	// Texture / Material manager
	WeakRef<Texture> RM_GetTexture(const std::string& path);
	bool RM_ImageLoadDone();
	void RM_FinishTextureLoad();
	Material RM_CreateMaterial();

}