#pragma once

#include "Gray/Core.h"
namespace Gray
{
	class VertexBuffer
	{
	private:
		unsigned int ID;

	public:
		VertexBuffer(void* data, unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
	};
}