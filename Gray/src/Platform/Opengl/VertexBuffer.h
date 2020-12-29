#pragma once

#include "Gray/Core.h"
namespace Gray
{

	class VertexBuffer
	{
	private:
		uint ID;
		static uint boundVB_ID;

	public:
		VertexBuffer(void* data, uint size);
		VertexBuffer(const VertexBuffer& vb) = delete;
		VertexBuffer(VertexBuffer&& vb) noexcept;

		~VertexBuffer();

		VertexBuffer& operator=(const VertexBuffer& vb) = delete;

		void Bind() const;
		void Unbind() const;
	};

}