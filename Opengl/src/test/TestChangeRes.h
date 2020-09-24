#pragma once

#include "Test.h"

namespace test
{
	class TestViewPort : public Test
	{
	private:
		int dimension[2];

	public:
		TestViewPort();
		~TestViewPort();

		void OnRender() override;
		void OnUpdate() override;
		void OnImGUIRender() override;

	};

}