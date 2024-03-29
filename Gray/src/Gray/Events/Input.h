#pragma once


namespace Gray
{
	class Input
	{
	public:
		static bool IsKeyPressed(int keyCode);
		static bool IsMouseButtonPressed(int mouseButton);

		static float GetMouseX();
		static float GetMouseY();
		static std::pair<float, float> GetMousePos();

		static float GetMouseDX();
		static float GetMouseDY();

	private:
		friend class Application;
		static float dmx, dmy; // Change in cursor position since last frame
	};

}