#include "grpch.h"

#include "ImguiLayer.h"

#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"


namespace Gray
{
	
	ImguiLayer::ImguiLayer()
	{
		wp = nullptr;
		wpName = WindowProvider::Unknown;
	}

	ImguiLayer::~ImguiLayer()
	{

	}

	void ImguiLayer::OnAttatch()
	{
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

		wpName = Window::GetProviderName();
		wp = Window::GetProvider();

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
	
	void ImguiLayer::ImguiBegin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		if (wpName == WindowProvider::GLFW)
			ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImguiLayer::ImguiEnd()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImguiLayer::OnUpdate()
	{
	
	}

	void ImguiLayer::OnImguiRender()
	{

	}

	void ImguiLayer::OnEvent(Event& e)
	{
		Layer::OnEvent(e);
	}

}