#include "Gray.h"
#include "grpch.h"

#include "Gray/Layers/ImguiLayer.h"

class Sandbox : public Gray::Application
{
public:
	Sandbox()
	{
		AddLayer(new Gray::ImguiLayer());
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