#pragma once

#include "imgui.h"
#include <string>

namespace Gray
{
	//Intended to be called on each frame updata, from OnImguiRender
	void FPSDebugInfo(float dt)
	{
		static int frames = 0;
		static float time = 0;
		static float fps = 0.0f;

		frames++;
		time += dt;
		if (frames == 100)
		{
			fps = frames / time;
			frames = 0;
			time = 0;
		}

		ImGui::Text(("FPS : " + std::to_string(fps)).c_str());
	}
}