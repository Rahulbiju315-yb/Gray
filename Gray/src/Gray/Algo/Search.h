#pragma once

namespace Gray
{
	template<typename T>
	using EqualsFunc = bool(*)(const T& t1, const T& t2);

	template<typename T>
	bool DefaultEqualsFunc(const T& t1, const T& t2)
	{
		return t1 == t2;
	}

	template <class T>
	int Bsearch(const std::vector<T>& vec, T ele)
	{
		int ub = static_cast<int>(vec.size());
		int lb = 0;
		int mid = 0;

		while (lb <= ub)
		{
			mid = (lb + ub) / 2;
			const T& midEle = vec[mid];

			if (ele < midEle)
			{
				ub = mid - 1;
			}

			else if(midEle < ele)
			{
				lb = mid + 1;
			}

			else
			{
				return mid;
			}
		}

		return -1;
	}
	
	template <class T>
	int Lsearch(const std::vector<T>& vec, const T& ele, EqualsFunc<T> equals = DefaultEqualsFunc<T>)
	{
		int k = 0;
		for (const T& t : vec)
		{
			if (equals(t, ele))
				return k;

			k++;
		}

		return -1;
	}

}