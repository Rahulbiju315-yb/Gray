#include "grpch.h"
#include "VertexBuffer.h"

#include <GL/glew.h>

namespace Gray
{
	uint VertexBuffer::boundVB_ID = 0;
	std::vector<VertexBuffer> unreferncedVB;

	VertexBuffer::VertexBuffer() : ID(0)
	{
	}

	void VertexBuffer::LoadBufferData(void* data, size_t size)
	{
		CreateIfEmpty();
		
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		Unbind();
	}

	void VertexBuffer::Bind() const
	{
		boundVB_ID = ID;
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VertexBuffer::Unbind() const
	{
		boundVB_ID = 0;
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	bool VertexBuffer::IsBound() const
	{
		return boundVB_ID == ID;
	}


	void VertexBuffer::CopyFrom(const VertexBuffer& vb)
	{
		ID = vb.ID;
	}

	void VertexBuffer::CreateIfEmpty()
	{
		if(ID == 0)
			glGenBuffers(1, &ID);
	}

	void VertexBuffer::Free()
	{
		glDeleteBuffers(1, &ID);
	}
}