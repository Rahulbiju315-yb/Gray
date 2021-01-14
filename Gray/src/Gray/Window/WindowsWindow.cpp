#include "grpch.h"

#include "WindowsWindow.h"

#include "Gray/Events/Input.h"
#include "Gray/Events/WindowsInput.h"

#include "Gray/Events/KeyEvent.h"
#include "Gray/Events/WindowEvent.h"
#include "Gray/Events/MouseEvent.h"
namespace Gray
{
	static bool isGlfwInit = false;
	WindowProvider Window::wp;

	WindowsWindow::WindowsWindow(const std::string& title, uint width, uint height)
	{
		this->title = title;
		this->width = width;
		this->height = height;
		
		OnInit();

		WindowsInput* inp = new WindowsInput();
		Input::SetInput(inp);
	}

	WindowsWindow::~WindowsWindow()
	{
		
	}

	void WindowsWindow::OnInit()
	{
		if (!isGlfwInit)
		{
			if (!glfwInit())
			{
				GRAY_CORE_FATAL("Error initialising glfw");
				return;
			}
			isGlfwInit = true;
		}

		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		Window::wp = WindowProvider::GLFW;

		if (!glfwWindow)
		{
			GRAY_CORE_FATAL("Error creating glfw window");
			glfwTerminate();
			return ;
		}

		glfwMakeContextCurrent(glfwWindow);

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			GRAY_CORE_FATAL("Glew not initialised");
		}

		data =  WindowData();
		glfwSetWindowUserPointer(glfwWindow, (void*)(&data));

		glfwSetKeyCallback(glfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data =  *(WindowData*)(glfwGetWindowUserPointer(window));

				if (data.listener != nullptr)
				{
					if (action == GLFW_PRESS)
					{
						KeyPressedEvent event(key, 0);
						data.listener->OnEvent(event);
					}

					else if (action == GLFW_REPEAT)
					{
						KeyPressedEvent event(key, 1);
						data.listener->OnEvent(event);
					}

					else if (action == GLFW_RELEASE)
					{
						KeyReleasedEvent event(key);
						data.listener->OnEvent(event);
					}
				}
			});

		glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow* window) 
			{
				WindowData& data =  *(WindowData *)(glfwGetWindowUserPointer(window));
				WindowClosedEvent event;

				if (data.listener != nullptr)
				{
					data.listener->OnEvent(event);
				}
			});

		glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data =  *(WindowData *)(glfwGetWindowUserPointer(window));
				if (data.listener != nullptr)
				{
					if (action == GLFW_PRESS)
					{
						MousePressedEvent event(button == GLFW_MOUSE_BUTTON_RIGHT ? MouseButton::Right :
							MouseButton::Left);
						data.listener->OnEvent(event);
					}

					else if (action == GLFW_RELEASE)
					{
						MouseReleasedEvent event(button == GLFW_MOUSE_BUTTON_RIGHT ? MouseButton::Right :
							MouseButton::Left);
						data.listener->OnEvent(event);
					}

				}
			});

		glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow* window, double x, double y)
			{
				int action = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
				WindowData& data =  *(WindowData*)(glfwGetWindowUserPointer(window));

				if (data.listener != nullptr)
				{
					if (action == GLFW_PRESS)
					{
						MouseDraggedEvent event((float)x, (float)y);
						data.listener->OnEvent(event);
					}

					else
					{
						MouseMovedEvent event((float)x, (float)y);
						data.listener->OnEvent(event);
					}
				}
			});

		glfwSetScrollCallback(glfwWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				if (data.listener != nullptr)
				{
					data.listener->OnEvent(event);
				}
			});

		provider = (void*)glfwWindow;
	}

	void WindowsWindow::PollEvents()
	{
		glfwPollEvents();
	}

	void WindowsWindow::OnUpdate()
	{
		PollEvents();
		glfwSwapBuffers(glfwWindow);
	}

	void WindowsWindow::OnRender()
	{
		
	}


	uint WindowsWindow::GetWidth() const
	{
		return width;
	}

	uint WindowsWindow::GetHeight() const
	{
		return height;
	}

	const std::string& WindowsWindow::GetTitle() const
	{
		return title;
	}

	void WindowsWindow::SetListener(EventListener* listener)
	{
		data.listener = listener;
	}

}