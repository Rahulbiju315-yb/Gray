#pragma once

#include "Shared.h"
#include "NoCopy.h"
#include "WeakRef.h"

namespace Gray
{
	enum class RBType //Render buffer Type
	{
		StencilRB,
		DepthRB,
		DepthStencilRB
	};

	class RenderBuffer
	{
	public:
		void CreateBuffer(RBType type, int width, int height);
		void Bind() const;
		void Unbind() const;
		
		bool IsBound() const;

		uint GetID() const;

	private:
		static uint boundRB_ID;
		uint ID;

		RenderBuffer();

		RenderBuffer(const RenderBuffer&) = default;
		RenderBuffer(RenderBuffer&&) = default;

		RenderBuffer& operator=(const RenderBuffer&) = default;
		RenderBuffer& operator=(RenderBuffer&&) = default;

		void CopyFrom(const RenderBuffer&);
		void CreateIfEmpty();
		void Free();

		friend class Shared<RenderBuffer>;
		friend class NoCopy<RenderBuffer>;
		friend class WeakRef<RenderBuffer>;

	};

	uint RBTypeToUINT(RBType type);
}