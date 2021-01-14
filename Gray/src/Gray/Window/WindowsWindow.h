#pragma once

#include "Window.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace Gray
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const std::string& title, uint width = 1200, uint height = 700);
		~WindowsWindow();

		void OnUpdate() override;
		void OnRender() override;
		void PollEvents() override;

		uint GetWidth() const override;
		uint GetHeight() const override;
		const std::string& GetTitle() const override;


		void SetListener(EventListener* listener) override;

		struct WindowData
		{
		public:

			WindowData()
			{
				listener = nullptr;
			}

			EventListener *listener;
		};

	protected:
		uint width;
		uint height;
		std::string title;
		GLFWwindow *glfwWindow;

		void OnInit() override;

		WindowData data;
	};
}