#include "grpch.h"
#include "IndexBuffer.h"

#include <GL/glew.h>

namespace Gray
{

	IndexBuffer::IndexBuffer(uint indices[], int count)
	{
		glGenBuffers(1, &ID);

		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), indices, GL_STATIC_DRAW);
		Unbind();

		this->count = count;
	}

	IndexBuffer::IndexBuffer(IndexBuffer&& ib) noexcept
		:ID(ib.ID),
		 count(ib.count)
	{
		ib.ID = 0;
		ib.count = 0;
	}

	IndexBuffer::~IndexBuffer()
	{
		if(ID != 0)
			glDeleteBuffers(1, &ID);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	int IndexBuffer::GetCount() const
	{
		return count;
	}
}