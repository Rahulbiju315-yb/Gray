#include<VertexArray.h>

#include <vector>

VertexArray::VertexArray(const VertexBuffer& buffer, const BufferLayout& layout)
{
	glGenVertexArrays(1, &ID);
	bind();

	buffer.bind();
	const std::vector<VertexAttrib> vec = layout.getVector();

	int offset = 0;
	for (int i = 0; i < vec.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, vec[i].count, vec[i].type, 
			vec[i].normalized, layout.getStride(), (void*)offset);

		offset += vec[i].count * sizeof(vec[i].type);
	}

	unbind();
}

VertexArray::~VertexArray()
{

}

void VertexArray::bind() const
{
	glBindVertexArray(ID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

