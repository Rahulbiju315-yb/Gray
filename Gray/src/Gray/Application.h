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

		virtual void Init() = 0;
		virtual void OnUpdate() = 0;

		void AddLayer(Layer* l);
		bool RemoveLayer(Layer* l);
		bool RemoveLayerAt(int i);

		void Run();
		uint GetWidth();
		uint GetHeight();
		void* GetProvider();
		WindowProvider GetProviderName();

		void OnWindowClosed(WindowClosedEvent& event) override;

		void OnEvent(Event& e) override;

		static Application* GetApp();
		static void SetApp(Application* app);

		static ImGuiContext* GetImguiContext();

	protected:
		void Clear();
		float GetDT();

		Window *window;
		ImguiLayer *imguiLayer;
		LayerStack ls;

		static Application* app;

	private:
		float lastTime;
	};

	Application* CreateApplication();
}
