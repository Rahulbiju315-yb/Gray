#include "grpch.h"
#include "Application.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Window/Window.h"
namespace Gray
{
	bool run = true;

	Application::Application()
	{
		window = Window::Create("Gray window", 1200, 700);
		window->AddWindowListener(this);
	}

	Application::~Application()
	{

	}

	void Application::OnWindowClosed(const WindowClosedEvent& event) 
	{
		run = false;
		GRAY_INFO("Window closed calles");
	}

	void Application::AddKeyListener(KeyListener* kl)
	{
		window->AddKeyListener(kl);
	}

	void Application::AddMouseListener(MouseListener* ml)
	{
		window->AddMouseListener(ml);
	}

	void Application::AddWindowListener(WindowListener* wl)
	{
		window->AddWindowListener(wl);
	}

	void Application::Run()
	{
		while (run)
		{
			window->OnUpdate();
		}
	}
}