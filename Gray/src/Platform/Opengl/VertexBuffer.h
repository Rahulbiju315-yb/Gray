#pragma once

#include "Gray/Util/ResourceManager.h"
#include "NoCopy.h"
#include "Shared.h"
namespace Gray
{

	class VertexBuffer
	{
	public:
		void Bind() const;
		void Unbind() const;
		bool IsBound() const;

		void LoadBufferData(void* data, size_t size);
	private:
		uint ID;
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
	};

}