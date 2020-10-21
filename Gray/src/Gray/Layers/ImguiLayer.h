#pragma once

#include "Layer.h"

namespace Gray
{
	class GRAY_API ImguiLayer : public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();

		void OnAttatch() override;
		void OnDetatch() override;

		void OnUpdate() override;
		
		void OnEvent(Event& e) override;
	};
}