#pragma once

namespace Gray
{
	class GRAY_API VertexBuffer
	{
	private:
		unsigned int ID;

	public:
		VertexBuffer(void* data, unsigned int size);
		~VertexBuffer();

		void bind() const;
		void unbind() const;
	};
}