#include "grpch.h"
#include "FrameBuffer.h"

namespace Gray
{
	uint FrameBuffer::boundFB_ID = 0;
	FrameBuffer::FrameBuffer() 
		: ID(0)
	{
	}

	void FrameBuffer::Bind() const
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

	void FrameBuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	bool FrameBuffer::IsBound() const
	{
		return ID == boundFB_ID;
	}

	void FrameBuffer::AddAttachment(const Texture& tex, AttachmentType type, int index)
	{
		CreateIfEmpty();
		Bind();

		uint attachmentType = AttachmentTypeToUINT(type);
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, tex.GetID(), 0);
	}

	void FrameBuffer::AddAttachment(const RenderBuffer& rb, AttachmentType type, int index)
	{
		CreateIfEmpty();
		Bind();

		uint attachmentType = AttachmentTypeToUINT(type);
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, rb.GetID(), 0);
	}

	bool FrameBuffer::IsComplete() const 
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


	void FrameBuffer::CopyFrom(const FrameBuffer& fb)
	{
		ID = fb.ID;
	}

	void FrameBuffer::CreateIfEmpty()
	{
		if(ID == 0)
			glGenFramebuffers(1, &ID);
	}

	void FrameBuffer::Free()
	{
		glDeleteFramebuffers(1, &ID);
	}

}