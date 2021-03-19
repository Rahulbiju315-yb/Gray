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
		
		virtual void OnInit() = 0;
		virtual void PreRender(float dt) = 0;
		virtual void Render(float dt) = 0;
		virtual void PostRender(float dt) = 0;
		
		Window *window;
		static Application* singleton;

	private:

		float lastTime;
		float GetDT();
		void DeltaCursorUpdate();

		class CursorUpdateListener : public EventListener
		{
		public:
			CursorUpdateListener();
			void OnEvent(Event& e);
			
			std::tuple<float, float> GetCursorPos();

		private:
			float mCX, mCY;
		};
	};

}
