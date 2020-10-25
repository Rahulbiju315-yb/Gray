#pragma once

#include "GLFW/glfw3.h"

#ifndef TO_INT(X)
	#define TO_INT(X) (int)X
#endif

namespace Gray
{
	enum class GRAY_API MouseCodes
	{
		MouseLeft = 0,
		MouseRight = 1,
		MouseMiddle = 2
	};
}