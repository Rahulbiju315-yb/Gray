#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"

namespace Gray
{
	class Renderer
	{
	public:
		void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
		void clear();
	};
}