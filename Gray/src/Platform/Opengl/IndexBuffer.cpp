#include "grpch.h"
#include "IndexBuffer.h"

#include <GL/glew.h>

namespace Gray
{
	IndexBuffer::IndexBuffer(unsigned int indices[], int count)
	{
		glGenBuffers(1, &ID);

		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		unbind();

		this->count = count;
	}

	IndexBuffer::~IndexBuffer()
	{

	}

	void IndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	int IndexBuffer::getCount() const
	{
		return count;
	}
}