#include "grpch.h"
#include "ImguiLayer.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"


#include "Gray/Application.h"

namespace Gray
{
	
	ImguiLayer::ImguiLayer()
	{
		
	}

	ImguiLayer::~ImguiLayer()
	{

	}

	void ImguiLayer::OnAttatch()
	{
		Application* app = Application::GetApp();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;   
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          
		io.BackendPlatformName = "imgui_impl_glfw";
		io.DisplaySize = ImVec2(app->GetWidth(), app->GetHeight());

		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;	

		
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

		wpName = Window::GetProviderName();
		wp = app->GetProvider();

		if (wpName == WindowProvider::GLFW)
			ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)(wp), true);
		else
			GRAY_CORE_WARN("ImGui Not initialised for current window provider");

	}

	void ImguiLayer::OnDetatch()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImguiLayer::OnUpdate()
	{
		ImguiBegin();
		ImguiEnd();
	}
	
	void ImguiLayer::ImguiBegin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		if (wpName == WindowProvider::GLFW)
			ImGui_ImplGlfw_NewFrame();
	}

	void ImguiLayer::ImguiEnd()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImguiLayer::OnEvent(Event& e)
	{
		Layer::OnEvent(e);
	}

}