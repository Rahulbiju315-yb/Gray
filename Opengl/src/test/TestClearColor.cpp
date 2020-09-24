#include "Test.h"
#include "TestClearColor.h"

#include <imgui.h>
#include <GL/glew.h>
#include <iostream>

namespace test
{
	
	TestClearColor::TestClearColor()
		: mColor{ 0.2f, 0.3f, 0.8f, 1.0f }
	{

	}

	TestClearColor::~TestClearColor()
	{
		std::cout << "Destroyed";
	}

	void TestClearColor::onUpdate(float dt)
	{

	}

	void TestClearColor::onRender()
	{
		glClearColor(mColor[0], mColor[1], mColor[2], mColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void TestClearColor::onImGUIRender()
	{
		ImGui::ColorEdit4("Background Color", mColor);
	}

}