#pragma once

#include "VertexBuffer.h"
#include "BufferLayout.h"
#include "Gray/Core.h"

namespace Gray
{
	class VertexArray
	{
	public:
		VertexArray();
		VertexArray(const VertexBuffer& buffer, const BufferLayout& layout);
		VertexArray(const VertexArray& va) = delete;
		VertexArray(VertexArray&& va) noexcept;

		~VertexArray();

		VertexArray& operator=(const VertexArray& va) = delete;
		VertexArray& operator=(VertexArray&& va) = delete;

		void Bind() const;
		void Unbind() const;
		
		void TransferTo(VertexArray& va);

	private:
		uint ID;
		static uint boundVA_ID;
	};
}