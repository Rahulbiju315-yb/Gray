#include "TestViewPort.h"

#include <GL/glew.h>
#include "imgui.h"

#include <iostream>
namespace test
{
	bool updateRequired;

	TestViewPort::TestViewPort()
		:dimension{ 640, 480 },
		leftCorner{0, 0}
	{

	}

	TestViewPort::~TestViewPort()
	{
		glViewport(0, 0, 640, 480);
		std::cout << "Destroyed TestViewPort instance";
	}

	void TestViewPort::onRender()
	{
		if (updateRequired)
		{
			glViewport(leftCorner[0], leftCorner[1], dimension[0], dimension[1]);
			updateRequired = false;
		}
	}

	void TestViewPort::onUpdate(float dt)
	{

	}

	void TestViewPort::onImGUIRender()
	{
		updateRequired = ImGui::SliderInt2("Change Width, Height", dimension, 100, 1000);
		updateRequired += ImGui::SliderInt2("Change Left Corner X and  Y", leftCorner, 0, 900);
	}
}