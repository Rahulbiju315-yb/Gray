#pragma once

#include <GL/glew.h>
#include <vector>

class VertexAttrib
{
public:
	unsigned int count;
	unsigned int type;
	bool normalized;
};

class BufferLayout
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
	void Push(unsigned int count)
	{
		//static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		attribs.push_back({count, GL_FLOAT, false});
		stride += count * sizeof(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		attribs.push_back({count, GL_UNSIGNED_INT, false});
		stride += count * sizeof(GL_UNSIGNED_INT);
	}

	template<>
	void Push<int>(unsigned int count)
	{
		attribs.push_back({count, GL_INT, false});
		stride += count * sizeof(GL_INT);
	}

	int GetStride() const
	{
		return stride;
	}

	const std::vector<VertexAttrib>& GetVector() const 
	{
		return attribs;
	}
};

