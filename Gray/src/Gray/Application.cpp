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
		
	}

	Application::~Application()
	{

	}
			
	// Window Closed event implementation
	void Application::OnWindowClosed(WindowClosedEvent& event) 
	{
		run = false;
		GRAY_INFO("Window closed called");
	}


	void Application::Run()
	{
		while (run)
		{
			window->OnUpdate();
		}
	}

	//Event  dispatch
	void Application::OnEvent(Event& e)
	{
		
	}
}