#include "grpch.h"
#include "VertexArray.h"

#include <vector>

namespace Gray
{
	VertexArray::VertexArray() : ID(0)
	{
	}

	VertexArray::VertexArray(const VertexBuffer& buffer, const BufferLayout& layout)
	{
		glGenVertexArrays(1, &ID);
		Bind();

		buffer.Bind();
		const std::vector<VertexAttrib> vec = layout.GetVector();

		size_t offset = 0;
		for (int i = 0; i < vec.size(); i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, vec[i].count, vec[i].type,
				vec[i].normalized, layout.GetStride(), (void*)offset);

			offset += vec[i].count * sizeof(vec[i].type);
		}

		buffer.Unbind();
		Unbind();
	}

	VertexArray::VertexArray(VertexArray&& va) noexcept
		: ID(va.ID)
	{
		va.ID = 0;
	}

	VertexArray::~VertexArray()
	{
		if(ID != 0)
			glDeleteVertexArrays(1, &ID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(ID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::TransferTo(VertexArray& va)
	{
		if (va.ID != 0)
			glDeleteVertexArrays(1, &(va.ID));
	}

}