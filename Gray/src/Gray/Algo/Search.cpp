#include "grpch.h"
#include "Search.h"

namespace Gray
{
	template<class T>
	int Bsearch(const std::vector<T>& vec, T ele)
	{
		int ub = vec.size();
		int lb = 0;
		int mid = 0;

		while (lb <= ub)
		{
			mid = (lb + ub) / 2;
			const T& midEle = vec[mid];

			if (midEle == ele)
			{
				return mid;
			}

			else if (midEle > ele)
			{
				ub = mid - 1;
			}

			else
			{
				lb = mid + 1;
			}
		}

		return -1;
	}

	template<class T>
	int Lsearch(const std::vector<T>& vec, T ele)
	{
		int k = 0;
		for (const T& t : vec)
		{
			if (t == ele)
				return k;

			k++;
		}

		return -1;
	}
}