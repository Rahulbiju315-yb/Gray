#pragma once

#include "VertexBuffer.h"
#include "BufferLayout.h"
#include "Gray/Core.h"

namespace Gray
{
	class VertexArray
	{

	private:
		unsigned int ID;

	public:
		VertexArray(const VertexBuffer& buffer, const BufferLayout& layout);
		~VertexArray();

		void Bind() const;
		void Unbind() const;
	};
}