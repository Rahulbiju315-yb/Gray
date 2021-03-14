#pragma once

#include "Gray/Events/EventListener.h"
#include "GLFW/glfw3.h"
#include "Callbacks.h"

namespace Gray
{

	class Window
	{
	public:	
		static Window* GetWindow(const std::string& title="Gray Window", uint width = 1200, uint height = 700);

		static void Update();
		static void PollEvents();

		static void AddListener(EventListener* listener);

		static uint GetWidth();
		static uint GetHeight();

		static void SetCursorEnabled(bool enable);
		static bool IsCursorEnabled();

		static const std::string& GetTitle();
		static GLFWwindow* GetGLFWwindow();
		
		static bool ShouldBeClosed();

	private:
		Window();
		Window(const Window&) = delete;
		Window(Window&&);

		void Initialize(const std::string& title, uint width, uint height);

		~Window();

		Window& operator=(const Window&) = delete;
		Window& operator=(Window&& src) = delete;

		void InitImgui();
		void DestroyImgui();

		void SetCallbacks();

		uint width;
		uint height;

		std::string title;
		Callbacks callbacks;
		GLFWwindow* glfwWindow;

		bool isCursorEn;

		static Window* singleton;

		friend class Application;
		friend void FrameBufferSizeCallback(GLFWwindow*, int width, int height);
	};
}