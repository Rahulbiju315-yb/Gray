#include "grpch.h"
#include "ImguiLayer.h"

#include "GL/glew.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"

#include "Platform/Opengl/test/TestMenu.h"
#include "Platform/Opengl/test/TestClearColor.h"

#include "Gray/Application.h"

namespace Gray
{
	// TEST

	test::TestMenu* testMenu; 

	//
	ImguiLayer::ImguiLayer()
	{

	}

	ImguiLayer::~ImguiLayer()
	{

	}

	void ImguiLayer::OnAttatch()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		Application* app = Application::GetApp();
		io.DisplaySize = ImVec2(app->GetWidth(), app->GetHeight());
		ImGui::StyleColorsDark();


		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

		testMenu = new test::TestMenu();
		testMenu->addTest<test::TestClearColor>("Clear Color");
	}

	void ImguiLayer::OnDetatch()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImguiLayer::OnUpdate()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		testMenu->onImGUIRender();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImguiLayer::OnEvent(Event& e)
	{

	}
}