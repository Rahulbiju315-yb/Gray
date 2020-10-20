#pragma once

#include "Core.h"
#include "Event/Event.h"
#include "Event/WindowEvent.h"
#include "Event/WindowListener.h"
#include "Window/Window.h"
namespace Gray
{
	class GRAY_API Application : public WindowListener
	{
	public:
		Application();
		~Application();

		void Run();
		void OnWindowClosed(const WindowClosedEvent& event) override;

		void AddKeyListener(KeyListener* kl);
		void AddMouseListener(MouseListener* ml);
		void AddWindowListener(WindowListener* wl);

	protected:
		Window *window;
	};

	Application* CreateApplication();
}
