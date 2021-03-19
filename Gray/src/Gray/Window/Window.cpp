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
	Window* Window::singleton = nullptr;

	void MessageCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam);

	Window* Window::GetWindow(const std::string& title, uint width, uint height)
	{
		if (!singleton)
		{
			singleton = new Window();
			singleton->Initialize(title, width, height);
		}

		return singleton;
	}

	Window::Window()
		: width(0), height(0), title("Gray Window"), glfwWindow(nullptr), isCursorEn(true)
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
		assert(singleton);
		PollEvents();
		glfwSwapBuffers(singleton->glfwWindow);
	}

	void Window::PollEvents()
	{
		assert(singleton);
		glfwPollEvents();
	}

	void Window::AddListener(EventListener* listener)
	{
		assert(singleton);
		singleton->callbacks.AddListener(listener);
	}

	uint Window::GetWidth()
	{
		assert(singleton);
		return singleton->width;
	}

	uint Window::GetHeight()
	{
		assert(singleton);
		return singleton->height;
	}

	void Window::SetCursorEnabled(bool enable)
	{
		assert(singleton);
		singleton->isCursorEn = enable;

		if(singleton->isCursorEn)
			glfwSetInputMode(Window::GetWindow()->GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			glfwSetInputMode(Window::GetWindow()->GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	}

	bool Window::IsCursorEnabled()
	{
		assert(singleton);
		return singleton->isCursorEn;
	}

	const std::string& Window::GetTitle()
	{
		assert(singleton);
		return singleton->title;
	}

	GLFWwindow* Window::GetGLFWwindow()
	{
		assert(singleton);
		return singleton->glfwWindow;
	}

	bool Window::ShouldBeClosed()
	{
		assert(singleton);
		return glfwWindowShouldClose(singleton->glfwWindow);
	}

	void Window::InitImgui()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
		ImGui_ImplGlfw_InitForOpenGL(singleton->glfwWindow, true);
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
					callbacks.PropogateEvent(event); 
				}

				else if (action == GLFW_REPEAT)
				{
					KeyPressedEvent event(key, 1);
					callbacks.PropogateEvent(event);
				}

				else if (action == GLFW_RELEASE)
				{
					KeyReleasedEvent event(key);
					callbacks.PropogateEvent(event);
				}
				
			});

		glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow* window) 
			{
				Callbacks& callbacks =  *(Callbacks*)(glfwGetWindowUserPointer(window));
				WindowClosedEvent event;

				callbacks.PropogateEvent(event);
			});

		glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				Callbacks& callbacks = *(Callbacks*)(glfwGetWindowUserPointer(window));

				if (action == GLFW_PRESS)
				{
					MousePressedEvent event(button);
					callbacks.PropogateEvent(event);
				}

				else if (action == GLFW_RELEASE)
				{
					MouseReleasedEvent event(button);
					callbacks.PropogateEvent(event);
				}
			});

		glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow* window, double x, double y)
			{
				int action = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
				Callbacks& callbacks = *(Callbacks*)(glfwGetWindowUserPointer(window));

				if (action == GLFW_PRESS)
				{
					MouseDraggedEvent event((float)x, (float)y);
					callbacks.PropogateEvent(event);
				}

				else
				{
					MouseMovedEvent event((float)x, (float)y);
					callbacks.PropogateEvent(event);
				}
				
			});

		glfwSetScrollCallback(glfwWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				Callbacks& callbacks = *(Callbacks*)(glfwGetWindowUserPointer(window));
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				callbacks.PropogateEvent(event);
			});
	}
	
	void FrameBufferSizeCallback(GLFWwindow*, int width, int height)
	{
		Window::singleton->width = width;
		Window::singleton->height = height;

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