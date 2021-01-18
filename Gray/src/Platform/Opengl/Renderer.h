#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Texture.h"

namespace Gray
{
	class Renderer
	{
	public:
		void DrawScreenQuad(const Shader& shader) const;
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, uint n_instances) const;
		void Clear() const;
	};
}