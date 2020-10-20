#include "grpch.h"

#include "TestMenu.h"
#include "imgui.h"

namespace Gray
{
	namespace test
	{
		TestMenu::TestMenu()
			:selected(false)
		{
			currentTest = nullptr;
		}

		TestMenu::~TestMenu()
		{
			delete currentTest;
		}

		void TestMenu::onImGUIRender()
		{
			if (selected)
			{
				bool backPressed = ImGui::Button("Return");
				currentTest->onImGUIRender();

				if (backPressed)
				{
					delete currentTest;
					selected = false;
				}
			}
			else
			{
				for (auto& testPair : tests)
				{
					bool pressed = ImGui::Button(testPair.first.c_str());

					if (pressed)
					{
						currentTest = testPair.second();
						selected = true;
					}
				}
			}
		}

		void TestMenu::onUpdate(float dt)
		{
			if (selected)
			{
				currentTest->onUpdate(dt);
			}
		}

		void TestMenu::onRender()
		{
			if (selected)
			{
				currentTest->onRender();
			}
		}

		bool TestMenu::isTestSelected()
		{
			return selected;
		}

		Test* TestMenu::getCurrentTest()
		{
			return currentTest;
		}

	}
}