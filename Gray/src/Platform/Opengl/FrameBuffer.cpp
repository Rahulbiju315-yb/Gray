#include "grpch.h"
#include "FrameBuffer.h"

namespace Gray
{
	FrameBuffer::FrameBuffer() : ID(0)
	{
		glGenFramebuffers(1, &ID);
	}

	FrameBuffer::FrameBuffer(const Texture& tex, int index) : FrameBuffer()
	{
		AddAttachment(tex, AttachmentType::Color, index);
	}

	FrameBuffer::FrameBuffer(FrameBuffer&& fb) noexcept:
		ID(std::move(fb.ID))
	{
		fb.ID = 0;
	}

	FrameBuffer::~FrameBuffer()
	{
		if(ID != 0)
			glDeleteFramebuffers(1, &ID);
	}

	void FrameBuffer::Bind()
	{
		if (!IsComplete())
		{
			GRAY_WARN("Attempting to bind an incomplete Framebuffer (ID = " + std::to_string(ID) + " )");
			GRAY_WARN("Will bind the default Framebuffer instead");
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER, ID);
		}
	}

	void FrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::AddAttachment(const Texture& tex, AttachmentType type, int index)
	{
		uint attachmentType = AttachmentTypeToUINT(type);
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, tex.GetID(), 0);
	}

	void FrameBuffer::AddAttachment(const RenderBuffer& rb, AttachmentType type, int index)
	{
		uint attachmentType = AttachmentTypeToUINT(type);
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, rb.GetID(), 0);
	}

	bool FrameBuffer::IsComplete()
	{
		return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	}

	uint AttachmentTypeToUINT(AttachmentType type)
	{
		uint attachmentType = 0;
		if (type == AttachmentType::Color)
		{
			attachmentType = GL_COLOR_ATTACHMENT0;
		}
		else if (type == AttachmentType::Depth)
		{
			attachmentType = GL_DEPTH_ATTACHMENT;
		}
		else if (type == AttachmentType::Stencil)
		{
			attachmentType = GL_STENCIL_ATTACHMENT;
		}
		else if (type == AttachmentType::DepthStencil)
		{
			attachmentType = GL_DEPTH_STENCIL_ATTACHMENT;
		}
		return attachmentType;
	}
}