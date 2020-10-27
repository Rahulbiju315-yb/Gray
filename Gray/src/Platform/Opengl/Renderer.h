#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"

namespace Gray
{
	class GRAY_API Renderer
	{
	public:
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
		void Clear();
	};
}