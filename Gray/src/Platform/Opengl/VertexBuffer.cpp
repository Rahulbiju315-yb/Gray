#include "grpch.h"
#include "VertexBuffer.h"

#include <GL/glew.h>

namespace Gray
{
	VertexBuffer::VertexBuffer(void* data, unsigned int size)
	{
		glGenBuffers(1, &ID);

		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		Unbind();
	}

	VertexBuffer::~VertexBuffer()
	{

	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}