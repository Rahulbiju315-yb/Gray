#pragma once

namespace Gray
{
	class  IndexBuffer
	{
	private:
		uint ID;
		int count;
		static uint boundIB_ID;

	public:
		IndexBuffer(uint indices[], int count);
		IndexBuffer(const IndexBuffer& ib) = delete;
		IndexBuffer(IndexBuffer&& ib) noexcept;

		~IndexBuffer();

		IndexBuffer& operator=(const IndexBuffer& ib) = delete;
		IndexBuffer& operator=(IndexBuffer&& ib) = delete;

		void  Bind() const;
		void Unbind() const;
		int GetCount() const;
	};
}