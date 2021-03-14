#pragma once
/*
* Temporary helper functions.
* To be moved into appropriate files later.
*/

namespace Gray
{
	class TempUtil
	{
	public:
		static void DisableCursor();
		static void EnableCursor();
		static float GetTime();
		static bool IsCursorEnabled();

	private:
		static bool isCursoEn;
	};
}