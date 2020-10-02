#pragma once

#include <VertexBuffer.h>
#include <BufferLayout.h>

class VertexArray
{

private:
	unsigned int ID;

public:
	VertexArray(const VertexBuffer& buffer, const BufferLayout& layout);
	~VertexArray();

	void bind() const;
	void unbind() const;
};