#pragma once

#include "VertexBuffer.h"
#include "BufferLayout.h"

namespace Gray
{
	class GRAY_API VertexArray
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