#pragma once

#include "Platform/Opengl/Texture.h"
#include "Gray/Graphics/Materials.h"

#include "glm/glm.hpp"

#include "Platform/Opengl/RenderData.h"

namespace Gray
{
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texCoord;

		Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texCoord) : 
			pos(pos), normal(normal), texCoord(texCoord)
		{
		}
	};


	class Mesh
	{
	public:
		Mesh();

		void SetupMesh(float* vertices, uint n_vert,
			 uint* indices, uint n_ind, const BufferLayout& layout);

		void SetupMesh(const RenderData& renderData);

		const RenderData& GetRenderData() const { return data; }
		Material& GetMaterial() const { return material; }

	private:
		mutable Material material;
		RenderData data;
	};
}