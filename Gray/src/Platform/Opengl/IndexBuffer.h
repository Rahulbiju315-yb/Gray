#pragma once

namespace Gray
{
	class GRAY_API  IndexBuffer
	{
	private:
		unsigned int ID;
		int count;

	public:
		IndexBuffer(unsigned int indices[], int count);
		~IndexBuffer();

		void  Bind() const;
		void Unbind() const;
		int GetCount() const;
	};
}