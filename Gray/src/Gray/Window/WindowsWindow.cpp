#include "grpch.h"
#include "WindowsWindow.h"



namespace Gray
{
	static bool isGlfwInit = false;
	
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
		if (!window)
		{
			GRAY_CORE_FATAL("Error creating glfw window");
			glfwTerminate();
			return ;
		}

		glfwMakeContextCurrent(window);


		data =  WindowData();
		glfwSetWindowUserPointer(window, (void*)(&data));

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data =  *(WindowData*)(glfwGetWindowUserPointer(window));

				if (action == GLFW_PRESS)
				{
					KeyPressedEvent event(key, 0);
					for (int i = 0; i < data.kls.size(); i++)
					{
						(data.kls.at(i))->OnKeyPressed(event);
					}
				}

				else if (action == GLFW_REPEAT)
				{
					KeyPressedEvent event(key, 1);
					for (int i = 0; i < data.kls.size(); i++)
					{
						(data.kls.at(i))->OnKeyPressed(event);
					}
				}

				else if (action == GLFW_RELEASE)
				{
					KeyReleasedEvent event(key);
					for (int i = 0; i < data.kls.size(); i++)
					{
						(data.kls.at(i))->OnKeyReleased(event);
					}
				}
			});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) 
			{
				WindowData& data =  *(WindowData *)(glfwGetWindowUserPointer(window));
				WindowClosedEvent event;
				for (int i = 0; i < data.wls.size(); i++)
				{
					(data.wls.at(i))->OnWindowClosed(event);
				}
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data =  *(WindowData *)(glfwGetWindowUserPointer(window));

				if (action == GLFW_PRESS)
				{
					MousePressedEvent event(button == GLFW_MOUSE_BUTTON_RIGHT ? MouseButton::Right : 
						MouseButton::Left);

					for (int i = 0; i < data.mls.size(); i++)
					{
						(data.mls.at(i))->OnMousePressed(event);
					}
				}

				else if (action == GLFW_RELEASE)
				{
					MouseReleasedEvent event(button == GLFW_MOUSE_BUTTON_RIGHT ? MouseButton::Right : 
						MouseButton::Left);


					for (int i = 0; i < data.mls.size(); i++)
					{
						(data.mls.at(i))->OnMouseReleased(event);
					}
				}

			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y)
			{
				int action = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
				WindowData& data =  *(WindowData*)(glfwGetWindowUserPointer(window));

				
				if (action == GLFW_PRESS)
				{
					MouseDraggedEvent event(x, y);
					for (int i = 0; i < data.mls.size(); i++)
					{
						(data.mls.at(i))->OnMouseDragged(event);
					}
				}

				else
				{
					MouseMovedEvent event(x, y);
					for (int i = 0; i < data.mls.size(); i++)
					{
						(data.mls.at(i))->OnMouseMoved(event);
					}
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

	void WindowsWindow::AddKeyListener(KeyListener* kl)
	{
		data.kls.push_back(kl);
	}

	void WindowsWindow::AddMouseListener(MouseListener* ml)
	{
		data.mls.push_back(ml);
	}

	void WindowsWindow::AddWindowListener(WindowListener* wl)
	{
		data.wls.push_back(wl);
	}
}