#pragma once
#include "Texture.h"
#include "RenderBuffer.h"
#include "NoCopy.h"
#include "Shared.h"
#include "WeakRef.h"
namespace Gray
{
	enum class AttachmentType
	{
		Depth,
		Stencil,
		DepthStencil,
		Color
	};

	class FrameBuffer
	{
	public:
		~FrameBuffer() = default;
		
		void Bind() const;
		void Unbind() const;
		bool IsBound() const;
	
		void AddAttachment(const Texture& tex, AttachmentType type, int index = 0);
		void AddAttachment(const RenderBuffer& rb, AttachmentType type, int index = 0);

		bool IsComplete() const;

	private:
		FrameBuffer();
		FrameBuffer(const FrameBuffer& fb) = default;
		FrameBuffer(FrameBuffer&& fb) = default;

		void CopyFrom(const FrameBuffer& va);
		void Free();

		uint ID;
		static uint boundFB_ID;
		
		friend class NoCopy<FrameBuffer>;
		friend class Shared<FrameBuffer>;
		friend class WeakRef<FrameBuffer>;

	};

	uint AttachmentTypeToUINT(AttachmentType type);
}