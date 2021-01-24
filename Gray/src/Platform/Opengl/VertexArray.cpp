#include "grpch.h"
#include "VertexArray.h"

#include <vector>

namespace Gray
{
	std::vector<VertexArray> unreferencedVA;
	uint VertexArray::boundVA_ID = 0;

	VertexArray::VertexArray() : ID(0),  n_attribs(0)
	{
	}

	void VertexArray::SetAttribPointers(const VertexBuffer& buffer, const BufferLayout& layout)
	{
		CreateIfEmpty();

		Bind();
		buffer.Bind();

		size_t offset = 0;
		const std::vector<VertexAttrib> vec = layout.GetVector();
		for (int i = 0; i < vec.size(); i++)
		{
			glEnableVertexAttribArray(n_attribs);
			
			glVertexAttribPointer(n_attribs, vec[i].count, vec[i].type,
				vec[i].normalized, layout.GetStride(), (void*)offset);
			offset += vec[i].count * sizeof(vec[i].type);

			n_attribs++;
		}

		buffer.Unbind();
		Unbind();
	}

	void VertexArray::Bind() const
	{
		boundVA_ID = ID;
		glBindVertexArray(ID);
	}

	void VertexArray::Unbind() const
	{
		boundVA_ID = 0;
		glBindVertexArray(0);
	}

	bool VertexArray::IsBound() const
	{
		return boundVA_ID == ID;
	}

	uint VertexArray::GetID() const
	{
		return ID;
	}

	void VertexArray::CopyFrom(const VertexArray& va)
	{
		ID = va.ID;
		n_attribs = va.n_attribs;
	}

	void VertexArray::CreateIfEmpty()
	{
		if(ID == 0)
			glGenVertexArrays(1, &ID);
	}

	void VertexArray::Free()
	{
		glDeleteVertexArrays(1, &ID);
	}
}