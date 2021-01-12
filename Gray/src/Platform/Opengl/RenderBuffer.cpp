#include "grpch.h"
#include "RenderBuffer.h"

namespace Gray
{

	std::vector<RenderBuffer> unreferencedRB;

	RenderBuffer::RenderBuffer() : ID(0)
	{
	}

	void RenderBuffer::CreateBuffer(RBType type, int width, int height)
	{
		CreateIfEmpty();
		Bind();

		uint rbType = RBTypeToUINT(type);
		glRenderbufferStorage(GL_RENDERBUFFER, rbType, width, height);
	}

	void RenderBuffer::Bind() const
	{
		boundRB_ID = ID;
		glBindRenderbuffer(GL_RENDERBUFFER, ID);
	}

	void RenderBuffer::Unbind() const
	{
		boundRB_ID = 0;
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	bool RenderBuffer::IsBound() const
	{
		return ID == boundRB_ID;
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

	void RenderBuffer::CopyFrom(const RenderBuffer& rb)
	{
		ID = rb.ID;
	}

	void RenderBuffer::CreateIfEmpty()
	{
		if(ID == 0)
		glGenRenderbuffers(1, &ID);
	}

	void RenderBuffer::Free()
	{
		glDeleteRenderbuffers(1, &ID);
	}

}