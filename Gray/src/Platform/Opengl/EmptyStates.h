#pragma once

#include "NoCopy.h"

namespace Gray
{
	template <class T>
	NoCopy<T>& Empty()
	{
		static NoCopy<T> emptyRes;
		return emptyRes;
	}
}