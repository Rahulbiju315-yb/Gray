#pragma once

#include "Test.h"

#include <string>
#include <functional>
#include <vector>
#include <iostream>

namespace test
{
	typedef std::pair <std::string, std::function<Test* ()>> TestPair;

	class TestMenu: public Test
	{
	private:
		std::vector <TestPair> tests;
		bool selected;
		Test* currentTest;

	public:
		TestMenu();
		~TestMenu();

		void onUpdate(float dt) override;
		void onRender() override;
		void onImGUIRender() override;

		template <typename T>
		void addTest(const std::string& name)
		{
			std::cout << "Registering " << name;
			tests.push_back(TestPair(name, []() { return new T(); }));
		}

		bool isTestSelected();

		Test* getCurrentTest();
	};
}