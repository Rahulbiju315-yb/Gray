#pragma once

#include <GL/glew.h>
#include <vector>

namespace Gray
{


	class VertexAttrib
	{
	public:
		uint count;
		uint type;
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
		void Push(uint count)
		{
			//static_assert(false);
		}

		template<>
		void Push<float>(uint count)
		{
			attribs.push_back({ count, GL_FLOAT, false });
			stride += count * sizeof(GL_FLOAT);
		}

		template<>
		void Push<uint>(uint count)
		{
			attribs.push_back({ count, GL_UNSIGNED_INT, false });
			stride += count * sizeof(GL_UNSIGNED_INT);
		}

		template<>
		void Push<int>(uint count)
		{
			attribs.push_back({ count, GL_INT, false });
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

}