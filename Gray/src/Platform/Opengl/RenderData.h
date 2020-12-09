#pragma once

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

namespace Gray
{
	struct RenderData
	{
		std::shared_ptr<VertexArray> va;
		std::shared_ptr<VertexBuffer> vb;
		std::shared_ptr<IndexBuffer> ib;
	};
}