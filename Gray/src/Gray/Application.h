#pragma once

#include "Window/Window.h"

#include "Events/AllListeners.h"

#include "Layers/LayerStack.h"
#include "Layers/ImguiLayer.h"
#include "Layers/RenderLayer.h"

#include "imgui.h"


namespace Gray
{
	class Application : public AllListeners
	{
	public:
		Application();
		~Application();

		virtual void Init();
		void AddLayer(Layer* l);
		bool RemoveLayer(Layer* l);
		bool RemoveLayerAt(int i);

		RenderLayer* GetRenderLayer();

		void Run();
		unsigned int GetWidth();
		unsigned int GetHeight();
		void* GetProvider();
		WindowProvider GetProviderName();

		void OnWindowClosed(WindowClosedEvent& event) override;

		void OnEvent(Event& e) override;

		static Application* GetApp();
		static void SetApp(Application* app);

		static ImGuiContext* GetImguiContext();

	protected:
		void Clear();

		Window *window;
		RenderLayer* renderLayer;
		ImguiLayer *imguiLayer;
		LayerStack ls;

		static Application* app;

	};

	Application* CreateApplication();
}
