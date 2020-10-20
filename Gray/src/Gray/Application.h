#pragma once

#include "Core.h"
#include "Window/Window.h"

#include "Events/AllListeners.h"

namespace Gray
{
	class GRAY_API Application : public AllListeners
	{
	public:
		Application();
		~Application();

		void Run();
		void OnWindowClosed(WindowClosedEvent& event) override;

		void OnEvent(Event& e) override;
	protected:
		Window *window;
	};

	Application* CreateApplication();
}
