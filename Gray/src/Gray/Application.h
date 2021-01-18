#pragma once

#include "Window/Window.h"

namespace Gray
{
	class Application
	{
	public:
		void Run();

		uint GetWidth();
		uint GetHeight();
		Window* GetWindow();
		static Application* GetApp();

	protected:
		Application();
		Application(const Application&) = delete;
		Application(Application&&) = delete;

		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) = delete;

		void Clear();
		
		virtual void OnInit() = 0;
		virtual void OnUpdate(float dt) = 0;
		virtual void OnImguiRender(float dt) = 0;
		
		Window *window;
		static Application* singleton;

	private:

		float lastTime;
		float GetDT();
	};

}
