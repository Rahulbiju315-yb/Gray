#pragma once

#include <GL/glew.h>
#include <vector>

class GRAY_API VertexAttrib
{
public:
	unsigned int count;
	unsigned int type;
	bool normalized;
};

class GRAY_API BufferLayout
{
private:
	std::vector<VertexAttrib> attribs;
	int stride;

public:
	BufferLayout()
	{
		stride = 0;
	}

	~BufferLayout()
	{

	}

	template<typename T>
	void push(unsigned int count)
	{
		//static_assert(false);
	}

	template<>
	void push<float>(unsigned int count)
	{
		attribs.push_back({count, GL_FLOAT, false});
		stride += count * sizeof(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		attribs.push_back({count, GL_UNSIGNED_INT, false});
		stride += count * sizeof(GL_UNSIGNED_INT);
	}

	template<>
	void push<int>(unsigned int count)
	{
		attribs.push_back({count, GL_INT, false});
		stride += count * sizeof(GL_INT);
	}

	int getStride() const
	{
		return stride;
	}

	const std::vector<VertexAttrib>& getVector() const 
	{
		return attribs;
	}
};

