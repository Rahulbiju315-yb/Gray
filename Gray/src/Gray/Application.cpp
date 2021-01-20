#include "grpch.h"

#include "Application.h"
#include "TempUtil.h"
#include "Events/Input.h"

namespace Gray
{
	bool run = true;
	Application* Application::singleton = nullptr;

	Application::Application() 
		: lastTime(-1), window(Window::GetWindow("Gray window", 1200, 700))
	{
		if (!singleton)
		{
			singleton = this;
			Log::Init();
		}
		else
		{
			GRAY_CORE_ERROR("Application already exists!! Cannot create another");
		}

	}

	void Application::Run()
	{
		OnInit();

		while (!window->ShouldBeClosed())
		{
			DeltaCursorUpdate();
			
			// Application update
			float dt = GetDT();
			OnUpdate(dt);

			// Imgui render
			window->BeginImgui();
			OnImguiRender(dt);
			window->EndImgui();

			//Window redraw
			window->OnUpdate();
		}
	}

	// Getters
	Application* Application::GetApp() { return singleton; }
	uint Application::GetWidth() { return window->GetWidth(); }
	uint Application::GetHeight() { return window->GetHeight(); }
	Window* Application::GetWindow() { return window; }


	float Application::GetDT()
	{
		float dt = 0;
		if (lastTime > 0)
		{
			dt = TempUtil::GetTime() - lastTime;
		}
		else
		{
			dt = 0;
		}
		lastTime = TempUtil::GetTime();

		return dt;
	}

	void Application::DeltaCursorUpdate()
	{
		static float mOX = Input::GetMouseX(), mOY = Input::GetMouseY();
		float mX = Input::GetMouseX();
		float mY = Input::GetMouseY();

		// Mouse position change since last frame
		Input::dmx = mX - mOX;
		Input::dmy = mY - mOY;

		mOX = mX;
		mOY = mY;
	}


}