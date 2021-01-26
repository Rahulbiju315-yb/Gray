#pragma once

#include "Platform/Opengl/Texture.h"
#include "Gray/Graphics/Materials.h"
#include "Gray/Mesh/MeshData.h"

#include "glm/glm.hpp"

#include "Platform/Opengl/VertexArray.h"
#include "Platform/Opengl/VertexBuffer.h"
#include "Platform/Opengl/IndexBuffer.h"

namespace Gray
{
	struct MeshRenderData
	{
		Shared<VertexBuffer> vb;
		Shared<VertexArray> va;
		Shared<IndexBuffer> ib;
	};

	struct ModelMesh
	{
		void SetupMesh(const MeshData& meshD, const BufferLayout& layout);

		Material material;
		MeshRenderData renderData;
	};
}