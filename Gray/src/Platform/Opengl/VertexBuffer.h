#pragma once

#include "NoCopy.h"
#include "Shared.h"
#include "WeakRef.h"

namespace Gray
{

	class VertexBuffer
	{
	public:
		void Bind() const;
		void Unbind() const;
		bool IsBound() const;

		size_t GetSize() { return size; }
		uint GetID() { return ID; }

		void LoadBufferData(const void* data, size_t size);
		void CopyBufferData(const VertexBuffer& src, uint rOffset, uint wOffset, size_t size);
		void AppendBufferData(const VertexBuffer& src);
	private:
		uint ID;
		size_t size;

		static uint boundVB_ID;
		
		VertexBuffer(); // Default unitialised state with ID = 0

		VertexBuffer(const VertexBuffer&) = default;
		VertexBuffer(VertexBuffer&&) = default;

		VertexBuffer& operator=(const VertexBuffer&) = default;
		VertexBuffer& operator=(VertexBuffer&&) = default;

		void CopyFrom(const VertexBuffer& vb);
		void CreateIfEmpty();
		void Free();

		friend class Shared<VertexBuffer>;
		friend class NoCopy<VertexBuffer>;
		friend class WeakRef<VertexBuffer>;
	};

}