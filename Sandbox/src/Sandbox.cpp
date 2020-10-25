#include "Gray.h"
#include "grpch.h"

#include "Gray/Layers/ImguiLayer.h"

#include "Platform/Opengl/test/Util.h"
#include "Platform/Opengl/Opengl.h"

#include "glm/glm.hpp"

#include "Gray/TempUtil.h"
#include "Gray/Events/Input.h"

#include "imgui.h"
#include "TestLayers.h"

class Sandbox : public Gray::Application
{
public:
	Sandbox()
	{
		// Init
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//EndInit

		Overlay* ov = new Overlay();

		AddLayer(ov);

		ImGui::SetCurrentContext(Gray::Application::GetImguiContext());
	}

	~Sandbox()
	{

	}

	void OnMouseDragged(Gray::MouseDraggedEvent& e) override
	{
		GRAY_INFO("Mouse Dragged Event OK");
	}

	void OnMousePressed(Gray::MousePressedEvent& e) override
	{
		GRAY_INFO("Mouse Pressed Event OK");
	}
};

Gray::Application* Gray::CreateApplication()
{
	return new Sandbox();
}