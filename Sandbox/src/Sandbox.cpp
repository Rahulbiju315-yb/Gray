#include "Gray.h"
#include "grpch.h"


class Sandbox : public Gray::Application, Gray::MouseListener
{
public:
	Sandbox()
	{
		AddMouseListener(this);
	}

	~Sandbox()
	{

	}

	void OnMouseDragged(const Gray::MouseDraggedEvent& e) override
	{
		GRAY_INFO("Mouse Dragged Event OK");
	}

	void OnMousePressed(const Gray::MousePressedEvent& e) override
	{
		GRAY_INFO("Mouse Pressed Event OK");
	}
};

Gray::Application* Gray::CreateApplication()
{
	return new Sandbox();
}