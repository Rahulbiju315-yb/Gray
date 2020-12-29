#include "grpch.h"
#include "VertexBuffer.h"

#include <GL/glew.h>

namespace Gray
{
	uint VertexBuffer::boundVB_ID = 0;
	std::vector<VertexBuffer> unreferncedVB;

	VertexBuffer::VertexBuffer(void* data, uint size) : ID(0)
	{
		glGenBuffers(1, &ID);

		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		Unbind();
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& vb) noexcept
		:ID(vb.ID)
	{
		vb.ID = 0;
	}

	VertexBuffer::~VertexBuffer()
	{
		if (ID != 0)
		{
			if (boundVB_ID == ID)
			{
				GRAY_WARN("Unrefernced and bound vertexBuffer going out of scope!!!");
				GRAY_WARN("Will be added to std::vector<VertexBuffer> unreferencedVB");

				unreferncedVB.push_back(std::move(*this));
			}


			glDeleteBuffers(1, &ID);
		}
	}

	void VertexBuffer::Bind() const
	{
		boundVB_ID = ID;
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}