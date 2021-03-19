#pragma once

#include "Platform/Opengl/VertexArray.h"
#include "Platform/Opengl/VertexBuffer.h"
#include "Platform/Opengl/IndexBuffer.h"

#include "MeshData.h"
#include "Gray/Graphics/Materials.h"

namespace Gray
{
	struct SharedMesh
	{
		Shared<VertexBuffer> vb;
		Shared<VertexArray> va;
		Shared<IndexBuffer> ib;
	};

	struct NoCopyMesh
	{
		NoCopy<VertexBuffer> vb;
		NoCopy<VertexArray> va;
		NoCopy<IndexBuffer> ib;
	};

	struct RenderableMesh
	{
		NoCopyMesh mesh;
		glm::mat4 modelMatrix;
		glm::mat4 invModelMatrix;
		Material material;
	};

	//Initialize NoCopy mesh from meshData assuming a buffer layout
	// for pos (3 * float), normals (3 * float) and tex coord(2 * float)
	NoCopyMesh CreateMeshPNT(const MeshData& meshD);
}