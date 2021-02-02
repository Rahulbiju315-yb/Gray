#include "grpch.h"
#include "IndexBuffer.h"

#include <GL/glew.h>

namespace Gray
{
	std::vector<IndexBuffer> unreferencedIB;
	uint IndexBuffer::boundIB_ID = 0;

	IndexBuffer::IndexBuffer() : ID(0), count(0)
	{
		glGenBuffers(1, &ID);
	}

	void IndexBuffer::Bind() const
	{
		boundIB_ID = ID;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void IndexBuffer::Unbind() const
	{
		boundIB_ID = 0;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	bool IndexBuffer::IsBound() const
	{
		return ID == boundIB_ID;
	}

	void IndexBuffer::LoadBufferData(const uint* indices, int count)
	{
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), indices, GL_STATIC_DRAW);
		this->count = count;
		Unbind();
	}

	int IndexBuffer::GetCount() const
	{
		return count;
	}

	uint IndexBuffer::GetID() const
	{
		return ID;
	}

	void IndexBuffer::CopyFrom(const IndexBuffer& ib)
	{
		ID = ib.ID;
		count = ib.count;
	}

	void IndexBuffer::Free()
	{
		glDeleteBuffers(1, &ID);
	}

}