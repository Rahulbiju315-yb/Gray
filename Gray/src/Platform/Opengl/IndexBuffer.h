#pragma once

#include "Shared.h"
#include "NoCopy.h"
#include "WeakRef.h"

namespace Gray
{
	class  IndexBuffer
	{
	
	public:
		void  Bind() const;
		void Unbind() const;
		bool IsBound() const;

		void LoadBufferData(const uint* indices, uint count);

		uint GetCount() const; 
		uint GetID() const;
	private:
		IndexBuffer();

		IndexBuffer(const IndexBuffer&) = default;
		IndexBuffer(IndexBuffer&&) = default;

		IndexBuffer& operator=(const IndexBuffer&) = default;
		IndexBuffer& operator=(IndexBuffer&&) = default;

		void CopyFrom(const IndexBuffer& va);
		void Free();

		uint ID;
		uint count; // Vertice count
		static uint boundIB_ID;

		friend class Shared<IndexBuffer>;
		friend class NoCopy<IndexBuffer>;
		friend class WeakRef<IndexBuffer>;

	};
}