#pragma once

#include "Gray/Util/ResourceManager.h"
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

		void LoadBufferData(uint indices[], int count);

		int GetCount() const; 

	private:
		IndexBuffer();

		IndexBuffer(const IndexBuffer&) = default;
		IndexBuffer(IndexBuffer&&) = default;

		IndexBuffer& operator=(const IndexBuffer&) = default;
		IndexBuffer& operator=(IndexBuffer&&) = default;

		void CopyFrom(const IndexBuffer& va);
		void CreateIfEmpty();
		void Free();

		uint ID;
		mutable int count; // Vertice count
		static uint boundIB_ID;

		friend class Shared<IndexBuffer>;
		friend class NoCopy<IndexBuffer>;
		friend class WeakRef<IndexBuffer>;

	};
}