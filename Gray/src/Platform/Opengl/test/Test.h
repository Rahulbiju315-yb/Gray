#pragma once

namespace Gray
{
	namespace test
	{
		class Test
		{
		public:
			Test() {}
			virtual ~Test() {}

			virtual void onUpdate(float dt) { }
			virtual void onRender() { }
			virtual void onImGUIRender() { }

		};
	}
}