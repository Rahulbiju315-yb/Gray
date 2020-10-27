#include "Gray.h"
#include "grpch.h"

#include "Gray/Layers/ImguiLayer.h"

#include "Platform/Opengl/test/Util.h"
#include "Platform/Opengl/Opengl.h"

#include "glm/glm.hpp"

#include "Gray/TempUtil.h"
#include "Gray/Events/Input.h"

#include "imgui.h"
#include "test/TestLayerCamera.h"
#include "test/TestLayerLightSource.h"

#include "Gray/Graphics/Camera.h"

//TO-DO
//1. Create Layer where Renderable objects can be added to(for debugging purposes)
//2. Add Imgui Rendering for camera with pos and dir vec display, toggle for camera movement.

class Sandbox : public Gray::Application
{
public:
	Sandbox()
	{
		Gray::TempUtil::DisableCursor();
		// Init
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//EndInit

		ImGui::SetCurrentContext(Gray::Application::GetImguiContext());
		AddLayer(new TestLayerLightSource());
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