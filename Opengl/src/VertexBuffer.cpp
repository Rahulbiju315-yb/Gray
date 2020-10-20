#include "grpch.h"
#include "VertexBuffer.h"

#include <GL/glew.h>

namespace Gray
{
	VertexBuffer::VertexBuffer(void* data, unsigned int size)
	{
		glGenBuffers(1, &ID);

		bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		unbind();
	}

	VertexBuffer::~VertexBuffer()
	{

	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}