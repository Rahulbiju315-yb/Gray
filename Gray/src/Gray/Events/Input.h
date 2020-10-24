#pragma once

namespace Gray
{
	class Input
	{
	public:
		static bool IsKeyPressed(int keyCode)
		{
			return input->IsKeyPressedImpl(keyCode);
		}

		static bool IsMouseButtonPressed(int mouseButton)
		{
			return input->IsMouseButtonPressedImpl(mouseButton);
		}

		virtual bool IsKeyPressedImpl(int keyCode);
		virtual bool IsMouseButtonPressedImpl(int mouseButton);
	private:
		static Input* input;
	};
}