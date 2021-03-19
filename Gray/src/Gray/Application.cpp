#include "grpch.h"

#include "Application.h"
#include "TempUtil.h"
#include "Events/Input.h"
#include "Platform/Opengl/Renderer.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include "ImGuizmo/ImGuizmo.h"

namespace Gray
{
	class ScrollListener;

	void BeginImgui();
	void EndImgui();

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
			ClearDepthColor();
			
			float dt = GetDT();
			PreRender(dt);

			// Application update
			Render(dt);

			BeginImgui();
			PostRender(dt);
			EndImgui();

			//Window redraw
			window->Update();

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
		static CursorUpdateListener l;
		static float ox = 0;
		static float oy = 0;

		auto [cmx, cmy] = l.GetCursorPos();
		Input::dmx = cmx - ox;
		Input::dmy = cmy - oy;

		ox = cmx;
		oy = cmy;
	}

	void BeginImgui()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();
	}

	void EndImgui()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}


	Application::CursorUpdateListener::CursorUpdateListener()
		: mCX(0), mCY(0)
	{
		Window::GetWindow()->AddListener(this);
	}

	void Application::CursorUpdateListener::OnEvent(Event& e)
	{
		Gray::EventType type = e.GetType();
		if (type == EventType::MouseMoved)
		{
			MouseMovedEvent& mme = (MouseMovedEvent&)e;
			mCX = mme.GetX();
		    mCY = mme.GetY();
		}

		if (type == EventType::MouseDragged)
		{
			MouseDraggedEvent& mme = (MouseDraggedEvent&)e;
			mCX = mme.GetX();
		    mCY = mme.GetY();
		}

	}

	std::tuple<float, float> Application::CursorUpdateListener::GetCursorPos()
	{
		return std::tuple<float, float>(mCX, mCY);
	}

}
