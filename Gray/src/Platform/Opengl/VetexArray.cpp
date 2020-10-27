#include "grpch.h"
#include "VertexArray.h"

#include <vector>

namespace Gray
{
	VertexArray::VertexArray(const VertexBuffer& buffer, const BufferLayout& layout)
	{
		glGenVertexArrays(1, &ID);
		Bind();

		buffer.Bind();
		const std::vector<VertexAttrib> vec = layout.GetVector();

		int offset = 0;
		for (int i = 0; i < vec.size(); i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, vec[i].count, vec[i].type,
				vec[i].normalized, layout.GetStride(), (void*)offset);

			offset += vec[i].count * sizeof(vec[i].type);
		}

		Unbind();
	}

	VertexArray::~VertexArray()
	{

	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(ID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

}