#pragma once

#include "Core.h"
#include "Window/Window.h"

#include "Events/AllListeners.h"
#include "Layers/LayerStack.h"

namespace Gray
{
	class GRAY_API Application : public AllListeners
	{
	public:
		Application();
		~Application();

		void AddLayer(Layer* l);
		bool RemoveLayer(Layer* l);
		bool RemoveLayerAt(int i);

		void Run();
		unsigned int GetWidth();
		unsigned int GetHeight();
		void* GetProvider();

		void OnWindowClosed(WindowClosedEvent& event) override;
		void OnEvent(Event& e) override;

		static Application* GetApp();
		static void SetApp(Application* app);

	protected:
		Window *window;
		LayerStack ls;

		static Application* app;
	};

	Application* CreateApplication();
}
