#include "grpch.h"
#include "IndexBuffer.h"

#include <GL/glew.h>

namespace Gray
{
	IndexBuffer::IndexBuffer(unsigned int indices[], int count)
	{
		glGenBuffers(1, &ID);

		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		Unbind();

		this->count = count;
	}

	IndexBuffer::~IndexBuffer()
	{

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