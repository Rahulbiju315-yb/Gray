#pragma once

#include "Platform/Opengl/Texture.h"
#include "Gray/Graphics/Materials.h"

#include "glm/glm.hpp"

#include "Platform/Opengl/VertexArray.h"
#include "Platform/Opengl/VertexBuffer.h"
#include "Platform/Opengl/IndexBuffer.h"
namespace Gray
{
	struct MeshRenderData
	{
		NoCopy<VertexBuffer> vb;
		NoCopy<VertexArray> va;
		NoCopy<IndexBuffer> ib;
	};

	class Mesh
	{
	public:
		Mesh();

		void SetupMesh(float* vertices, uint n_vert,
			 uint* indices, uint n_ind, const BufferLayout& layout);

		Material material;
		MeshRenderData renderData;
	};
}