#pragma once
#include "Texture.h"
#include "RenderBuffer.h"

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
		FrameBuffer();
		FrameBuffer(const Texture& tex, int index=0); // Color attachment texture
		FrameBuffer(const FrameBuffer& fb) = delete;
		FrameBuffer(FrameBuffer&& fb) noexcept;

		~FrameBuffer();

		FrameBuffer& operator=(const FrameBuffer& fb) = delete;
		

		void Bind();
		void Unbind();
		void AddAttachment(const Texture& tex, AttachmentType type, int index=0);
		void AddAttachment(const RenderBuffer& rb, AttachmentType type, int index=0);

		bool IsComplete();

	private:
		uint ID;
	};

	uint AttachmentTypeToUINT(AttachmentType type);
}