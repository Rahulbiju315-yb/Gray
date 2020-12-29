#include "grpch.h"
#include "RenderBuffer.h"

namespace Gray
{
	RenderBuffer::RenderBuffer() : ID(0)
	{
	}

	RenderBuffer::RenderBuffer(RenderBuffer&& rb) noexcept :
		ID(std::move(rb.ID))
	{
		rb.ID;
	}

	RenderBuffer::~RenderBuffer()
	{
		if (ID != 0)
			glDeleteRenderbuffers(1, &ID);
	}

	void RenderBuffer::CreateBuffer(RBType type, int width, int height) const
	{
		uint rbType = RBTypeToUINT(type);
		glRenderbufferStorage(GL_RENDERBUFFER, rbType, width, height);
	}

	void RenderBuffer::Bind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, ID);
	}

	void RenderBuffer::Unbind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	uint RenderBuffer::GetID() const
	{
		return ID;
	}

	uint RBTypeToUINT(RBType type)
	{
		uint rbType = 0;
		if (type == RBType::StencilRB)
		{
			rbType = GL_STENCIL_INDEX;
		}
		else if (type == RBType::DepthRB)
		{
			rbType = GL_DEPTH_COMPONENT;
		}
		else if (type == RBType::DepthStencilRB)
		{
			rbType = GL_DEPTH24_STENCIL8;
		}

		return rbType;
	}
}