#include "grpch.h"

#include "Application.h"

namespace Gray
{
	bool run = true;
	Application* Application::app = nullptr;


	Application::Application()
	{
		window = Window::Create("Gray window", 1200, 700);
		window->SetListener(this);
		Application::SetApp(this);
	}

	Application::~Application()
	{

	}

	void Application::Init()
	{
		imguiLayer = new ImguiLayer();
		imguiLayer->OnAttatch();

		renderLayer = new RenderLayer();
		renderLayer->OnAttatch();
		AddLayer(renderLayer);
	}
	//---
	
	void Application::AddLayer(Layer* l)
	{
		l->OnAttatch();
		ls.PushLayer(l);
	}

	bool Application::RemoveLayer(Layer* l)
	{
		return ls.RemoveLayer(l);
	}

	bool Application::RemoveLayerAt(int i)
	{
		return ls.RemoveLayer(ls.LayerAt(i));
	}

	RenderLayer* Application::GetRenderLayer()
	{
		return renderLayer;
	}

	//---



	//---

	void Application::OnWindowClosed(WindowClosedEvent& event) 
	{
		run = false;
		GRAY_INFO("Window closed called");
	}

	//---

	

	//---

	void Application::Run()
	{
		Init();
		while (run)
		{
			//Clear();

			for (Layer *layer : ls)
				layer->OnUpdate();

			for (Layer* layer : ls)
			{
				imguiLayer->ImguiBegin();
				layer->OnImguiRender();
				imguiLayer->ImguiEnd();
			}

			window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		AllListeners::OnEvent(e);

		for (std::vector<Layer*>::reverse_iterator x = ls.rbegin(); x != ls.rend(); x++)
		{
			(*x)->OnEvent(e);
		}
	}

	Application* Application::GetApp()
	{
		return app;
	}

	void Application::SetApp(Application* app)
	{
		if (Application::app == nullptr)
			Application::app = app;
		else
		{
			GRAY_CORE_ERROR("Application already exists");
		}
	}

	ImGuiContext* Application::GetImguiContext()
	{
		return ImGui::GetCurrentContext();
	}

	void Application::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	unsigned int Application::GetWidth()
	{
		return window->GetWidth();
	}
	
	unsigned int Application::GetHeight()
	{
		return window->GetHeight();
	}

	void* Application::GetProvider()
	{
		return window->GetProvider();
	}

	WindowProvider Application::GetProviderName()
	{
		return window->GetProviderName();
	}
	//---

}