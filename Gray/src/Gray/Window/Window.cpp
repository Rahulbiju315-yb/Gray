#include "grpch.h"

#include "Window.h"
#include "GL/glew.h"

#include "Gray/Events/MouseEvent.h"
#include "Gray/Events/KeyEvent.h"
#include "Gray/Events/WindowEvent.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include "ImGuizmo/ImGuizmo.h"

namespace Gray
{
	Window Window::singleton;
	void MessageCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam);

	Window* Window::GetWindow(const std::string& title, uint width, uint height)
	{
		if (!singleton.initialized)
		{
			singleton.Initialize(title, width, height);
			singleton.initialized = true;
		}

		return &singleton;
	}

	Window::Window()
		: width(0), height(0), title("Gray Window"), initialized(false), glfwWindow(nullptr)
	{
	}

	Window::~Window()
	{
		DestroyImgui();
		glfwTerminate();
	}

	void Window::Initialize(const std::string& title, uint width, uint height)
	{
		if (!glfwInit())
		{
			GRAY_CORE_FATAL("Error initialising glfw");
			return;
		}


		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//glfwGetPrimaryMonitor()
		glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		if (!glfwWindow)
		{
			GRAY_CORE_FATAL("Error creating glfw window");
			glfwTerminate();
			return ;
		}


		glfwMakeContextCurrent(glfwWindow);
		glfwSetFramebufferSizeCallback(glfwWindow, FrameBufferSizeCallback);

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			GRAY_CORE_FATAL("Glew not initialised");
		}

		glfwSwapInterval(1);


		// During init, enable debug output
		//glEnable              ( GL_DEBUG_OUTPUT );
		//glDebugMessageCallback( MessageCallback, 0 );
		InitImgui();
		SetCallbacks();
	}

	void Window::Update()
	{
		PollEvents();
		glfwSwapBuffers(glfwWindow);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::AddListener(EventListener* listener)
	{
		callbacks.AddListener(listener);
	}

	uint Window::GetWidth() const
	{
		return width;
	}

	uint Window::GetHeight() const
	{
		return height;
	}

	const std::string& Window::GetTitle() const
	{
		return title;
	}

	GLFWwindow* Window::GetGLFWwindow()
	{
		return glfwWindow;
	}

	bool Window::ShouldBeClosed()
	{
		return glfwWindowShouldClose(glfwWindow);
	}


	void Window::InitImgui()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
		ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	}

	void Window::DestroyImgui()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void Window::SetCallbacks()
	{
		glfwSetWindowUserPointer(glfwWindow, (void*)(&callbacks));

		glfwSetKeyCallback(glfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				Callbacks& callbacks =  *(Callbacks*)(glfwGetWindowUserPointer(window));

				if (action == GLFW_PRESS)
				{
					KeyPressedEvent event(key, 0);
					callbacks.PropogateEvent(event, EventType::KeyPressed); 
				}

				else if (action == GLFW_REPEAT)
				{
					KeyPressedEvent event(key, 1);
					callbacks.PropogateEvent(event, EventType::KeyPressed);
				}

				else if (action == GLFW_RELEASE)
				{
					KeyReleasedEvent event(key);
					callbacks.PropogateEvent(event, EventType::KeyReleased);
				}
				
			});

		glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow* window) 
			{
				Callbacks& callbacks =  *(Callbacks*)(glfwGetWindowUserPointer(window));
				WindowClosedEvent event;

				callbacks.PropogateEvent(event, EventType::WindowClosed);
			});

		glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				Callbacks& callbacks = *(Callbacks*)(glfwGetWindowUserPointer(window));

				if (action == GLFW_PRESS)
				{
					MousePressedEvent event(button == GLFW_MOUSE_BUTTON_RIGHT ? MouseButton::Right :
						MouseButton::Left);
					callbacks.PropogateEvent(event, EventType::KeyPressed);
				}

				else if (action == GLFW_RELEASE)
				{
					MouseReleasedEvent event(button == GLFW_MOUSE_BUTTON_RIGHT ? MouseButton::Right :
						MouseButton::Left);
					callbacks.PropogateEvent(event, EventType::KeyReleased);
				}
			});

		glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow* window, double x, double y)
			{
				int action = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
				Callbacks& callbacks = *(Callbacks*)(glfwGetWindowUserPointer(window));

				if (action == GLFW_PRESS)
				{
					MouseDraggedEvent event((float)x, (float)y);
					callbacks.PropogateEvent(event, EventType::MouseDragged);
				}

				else
				{
					MouseMovedEvent event((float)x, (float)y);
					callbacks.PropogateEvent(event, EventType::MouseMoved);
				}
				
			});

		glfwSetScrollCallback(glfwWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				Callbacks& callbacks = *(Callbacks*)(glfwGetWindowUserPointer(window));
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				callbacks.PropogateEvent(event, EventType::MouseScrolled);
			});
	}
	
	void FrameBufferSizeCallback(GLFWwindow*, int width, int height)
	{
		Window::singleton.width = width;
		Window::singleton.height = height;

		glViewport(0, 0, width, height);
	}

	void MessageCallback(GLenum source, GLenum type, GLuint id, 
		GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		
	  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			   ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
				type, severity, message );

	}
}