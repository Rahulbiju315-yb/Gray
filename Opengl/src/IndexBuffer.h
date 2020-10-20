#pragma once

namespace Gray
{
	class IndexBuffer
	{
	private:
		unsigned int ID;
		int count;

	public:
		IndexBuffer(unsigned int indices[], int count);
		~IndexBuffer();

		void  bind() const;
		void unbind() const;
		int getCount() const;
	};
}