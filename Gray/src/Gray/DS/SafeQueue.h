#pragma once

#include <vector>
#include <mutex>
#include <thread>

namespace Gray
{
	template <class T>
	class SafeQueue
	{
	public:
		SafeQueue()
			: head(-1)
		{

		}

		void Enqueue(const T& t)
		{
			std::scoped_lock<std::mutex> lock(vecMutex);
			vec.push_back(t);
			if (head == -1)
				head = 0;
		}

		void Enqueue(T&& t)
		{
			std::scoped_lock<std::mutex> lock(vecMutex);
			vec.push_back(std::move(t));
			if (head == -1)
				head = 0;
		}

		void DequeueTo(T& t)
		{
			std::scoped_lock<std::mutex> lock(vecMutex);
			if (head != -1)
			{
				t = std::move(vec[head]);
				head++;
			}

			if (head == vec.size())
			{
				vec.clear();
				head = -1;
			}
		}

		bool IsEmpty()
		{
			std::scoped_lock<std::mutex> lock(vecMutex);
			return vec.size() == 0;
		}

	private:		
		std::vector<T> vec;
		std::mutex vecMutex;
		int head;
	};
}