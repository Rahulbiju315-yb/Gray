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

		void Render();
		void PollEvents();

		void AddListener(EventListener* listener);

		uint GetWidth() const;
		uint GetHeight() const;
		const std::string& GetTitle() const;

		GLFWwindow* GetGLFWwindow();

		bool ShouldBeClosed();

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
		
		void BeginImgui();
		void EndImgui();

		void SetCallbacks();
		void InitGlew();

		uint width;
		uint height;

		std::string title;
		Callbacks callbacks;
		GLFWwindow* glfwWindow;

		bool initialized;

		static Window singleton;

		friend class Application;
		friend void FrameBufferSizeCallback(GLFWwindow*, int width, int height);
	};
}