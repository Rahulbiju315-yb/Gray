#pragma once

#include "Platform/Opengl/Texture.h"
#include "Platform/Opengl/Shader.h"
#include "Gray/Graphics/Materials.h"
#include "Gray/Graphics/Model/Model.h"

namespace Gray
{

	WeakRef<Texture> GetTexture(const std::string& path, bool flipTextures = true);
	void ReloadModel(const std::string& path, bool flipTexture);

	Material CreateMaterial();
	Model GetModel(std::string path, bool flipTexture = true);
	Shared<Shader> RMGetShader(const std::string& path);
	void RMReloadShaders();

	WeakRef<Texture> GetTextureParallel(const std::string& path);
	bool LoadTexIfFree();

	struct Image
	{
		unsigned char* data;
		std::string path;
		int width;
		int height;
		int nrChannels;
	};
}