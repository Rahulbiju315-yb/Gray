#pragma once

#include "Core.h"
#include "Event/Event.h"

namespace Gray
{
	class GRAY_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	};

	Application* CreateApplication();
}
