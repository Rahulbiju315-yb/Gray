#pragma once

#include "Platform/Opengl/Texture.h"
#include "Gray/Image/Image.h"

namespace Gray
{
	struct TextureImage
	{
		WeakRef<Texture> tex;
		Image im;
	};
}