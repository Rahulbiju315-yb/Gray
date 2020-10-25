#include "grpch.h"
#include "Input.h"

namespace Gray
{
	class GRAY_API WindowsInput : public Input
	{
	public:
		bool IsKeyPressedImpl(int keyCode) override;
		bool IsMouseButtonPressedImpl(int mouseButton) override;

		std::pair<float, float> GetMousePosImpl() override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
	};
}