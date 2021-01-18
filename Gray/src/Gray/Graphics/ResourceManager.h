#pragma once

#include "Platform/Opengl/Texture.h"
#include "Materials.h"
#include "Model/Model.h"

namespace Gray
{

	const Texture* GetTexture(const std::string& path, bool flipTextures = true);
	Material CreateMaterial();
	Model GetModel(std::string path, bool flipTexture = true);
}