#pragma once

#include "Layer.h"
#include "Gray/Window/Window.h"
namespace Gray
{
	class GRAY_API ImguiLayer : public Layer
	{
	public:

		ImguiLayer();
		~ImguiLayer();

		void OnAttatch() override;
		void OnDetatch() override;

		void OnUpdate() override;
		void ImguiBegin();
		void ImguiEnd();

		void OnEvent(Event& e) override;

	protected:
		WindowProvider wpName;
		void* wp;
	};
}