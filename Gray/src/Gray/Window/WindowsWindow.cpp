#include "grpch.h"
#include "WindowsWindow.h"



namespace Gray
{
	static bool isGlfwInit = false;
	WindowProvider Window::wp;

	WindowsWindow::WindowsWindow(const std::string& title, unsigned int width, unsigned int height)
	{
		this->title = title;
		this->width = width;
		this->height = height;
		
		OnInit();
	}

	WindowsWindow::~WindowsWindow()
	{
		delete window;
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

		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		Window::wp = WindowProvider::GLFW;

		if (!window)
		{
			GRAY_CORE_FATAL("Error creating glfw window");
			glfwTerminate();
			return ;
		}

		glfwMakeContextCurrent(window);

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			GRAY_CORE_FATAL("Glew not initialised");
		}	

		data =  WindowData();
		glfwSetWindowUserPointer(window, (void*)(&data));

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
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

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) 
			{
				WindowData& data =  *(WindowData *)(glfwGetWindowUserPointer(window));
				WindowClosedEvent event;

				if (data.listener != nullptr)
				{
					data.listener->OnEvent(event);
				}
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
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

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y)
			{
				int action = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
				WindowData& data =  *(WindowData*)(glfwGetWindowUserPointer(window));

				if (data.listener != nullptr)
				{
					if (action == GLFW_PRESS)
					{
						MouseDraggedEvent event(x, y);
						data.listener->OnEvent(event);
					}

					else
					{
						MouseMovedEvent event(x, y);
						data.listener->OnEvent(event);
					}
				}
			});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
				MouseScrolledEvent event(xOffset, yOffset);
				if (data.listener != nullptr)
				{
					data.listener->OnEvent(event);
				}
			});
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowsWindow::OnRender()
	{
		
	}

	unsigned int WindowsWindow::GetWidth() const
	{
		return width;
	}

	unsigned int WindowsWindow::GetHeight() const
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

	void* WindowsWindow::GetProvider() const
	{
		return (void*)window;
	}

}