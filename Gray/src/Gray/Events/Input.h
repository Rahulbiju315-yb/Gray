#pragma once

namespace Gray
{
	class Input
	{
	public:
		static bool IsKeyPressed(int keyCode)
		{
			if (!(input == nullptr))
				return input->IsKeyPressedImpl(keyCode);
			else
				return false;
		}

		static bool IsMouseButtonPressed(int mouseButton)
		{
			if (!(input == nullptr))
				return input->IsMouseButtonPressedImpl(mouseButton);
			else
				return false;
		}

		static float GetMouseX()
		{
			if (!(input == nullptr))
				return input->GetMouseXImpl();
			else
				return 0.0f;
		}

		static float GetMouseY()
		{
			if (!(input == nullptr))
				return input->GetMouseYImpl();
			else
				return 0.0f;
		}

		static std::pair<float, float> GetMousePos()
		{
			if(!(input == nullptr))
				return input->GetMousePosImpl();
			else
				return {0.0f, 0.0f};
			
		}

		static void SetInput(Input* input)
		{
			if(Input::input == nullptr)
				Input::input = input;
			else
			{
				GRAY_CORE_WARN("Input instance already set !!");
			}
		}

		virtual bool IsKeyPressedImpl(int keyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(int mouseButton) = 0;

		virtual  float GetMouseXImpl() = 0;
		virtual  float GetMouseYImpl() = 0;
		virtual  std::pair<float, float> GetMousePosImpl() = 0;

	private:
		static Input* input;
	};
}