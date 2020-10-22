#include "Gray.h"
#include "grpch.h"

#include "Gray/Layers/ImguiLayer.h"


#include "Platform/Opengl/test/MainTest.h"
#include "Platform/Opengl/test/TestMenu.h"

class TestLayer : public Gray::ImguiLayer
{
public:
	void OnAttatch() override
	{
		ImguiLayer::OnAttatch();
		testMenu = new Gray::test::TestMenu();
		testMenu->addTest<Gray::test::MainTest>("Main Test");
	}

	void OnUpdate() override
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImguiBegin();

		testMenu->onImGUIRender();
		testMenu->onRender();

		ImguiEnd();
	}

private:
	Gray::test::TestMenu* testMenu;
};

class Sandbox : public Gray::Application
{
public:
	Sandbox()
	{

		AddLayer(new TestLayer());

		// Init
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//EndInit
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