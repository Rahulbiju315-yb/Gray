#pragma once

#include "Platform/Opengl/Texture.h"
#include "Gray/Graphics/Material.h"
#include "Gray/Mesh/MeshData.h"

#include "glm/glm.hpp"

#include "Platform/Opengl/VertexArray.h"
#include "Platform/Opengl/VertexBuffer.h"
#include "Platform/Opengl/IndexBuffer.h"

#include "Gray/Mesh/Mesh.h"
namespace Gray
{
	struct ModelMesh
	{
		void SetupMesh(const MeshData& meshD, const BufferLayout& layout);

		Material material;
		SharedMesh renderData;
	};
}