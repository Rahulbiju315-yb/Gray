#pragma once

#include "Platform/Opengl/Texture.h"
#include "Platform/Opengl/Shader.h"
#include "Gray/Graphics/Materials.h"
#include "Gray/Graphics/Model/Model.h"

namespace Gray
{
	const std::string DEFAULT_SHADER = "res/models/shaders/shader.shader";

	//WeakRef<Texture> GetTexture(const std::string& path, bool flipTextures = true);
	//void ReloadModel(const std::string& path, bool flipTexture);
	void AddModelFileForImport(const std::string& path);
	bool TryLoadSceneForModel(Model& m);
	void CancelModelLoading();

	Material CreateMaterial();

	bool IsModelLoaded(const std::string& path);
	Model GetModel(const std::string& path);

	Shared<Shader> RMGetShader(const std::string& path);
	void RMReloadShaders();

	WeakRef<Texture> GetTexture(const std::string& path);
	bool ImageLoadDone();

	struct Image
	{
		unsigned char* data;
		std::string path;
		int width;
		int height;
		int nrChannels;
	};
}