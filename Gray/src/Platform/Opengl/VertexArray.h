#pragma once

#include "VertexBuffer.h"
#include "BufferLayout.h"
#include "NoCopy.h"
#include "Shared.h"
#include "WeakRef.h"

namespace Gray
{
	class VertexArray
	{
	public:
		void SetAttribPointers(const VertexBuffer& buffer, const BufferLayout& layout);
		void Bind() const;
		void Unbind() const;

		bool IsBound() const;
	private:
		uint ID;
		static uint boundVA_ID;

		VertexArray();

		VertexArray(const VertexArray&) = default;
		VertexArray(VertexArray&&) = default;

		VertexArray& operator=(const VertexArray&) = default;
		VertexArray& operator=(VertexArray&&) = default;

		void CopyFrom(const VertexArray& va);
		void CreateIfEmpty();
		void Free();

		friend class Shared<VertexArray>;
		friend class NoCopy<VertexArray>;
		friend class WeakRef<VertexArray>;

	};
}