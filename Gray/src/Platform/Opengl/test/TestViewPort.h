#pragma once

#include "Test.h"

namespace Gray
{
	namespace test
	{
		class TestViewPort : public Test
		{
		private:
			int dimension[2];
			int leftCorner[2];

		public:
			TestViewPort();
			~TestViewPort();

			void onRender() override;
			void onUpdate(float dt) override;
			void onImGUIRender() override;

		};
	}
}