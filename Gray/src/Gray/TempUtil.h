#pragma once
/*
* Temporary helper functions.
* To be moved into appropriate files later.
*/

#include "GLFW/glfw3.h"

namespace Gray
{
	class GRAY_API TempUtil
	{
	public:
		static void DisableCursor();
		static float GetTime();
	};
}