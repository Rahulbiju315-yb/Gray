#pragma once

#include "Test.h"

namespace test
{
	class TestClearColor: public Test
	{
	private:
		float mColor[4];

	public:
		TestClearColor();
		~TestClearColor();

		void onUpdate(float dt) override;
		void onRender() override;
		void onImGUIRender() override;
	};
}