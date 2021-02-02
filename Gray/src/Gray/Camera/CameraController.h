#pragma once

#include "EditorCamera.h"
#include "SceneCamera.h"

namespace Gray
{
	class CameraController
	{
	public:
		static void Control(EditorCamera& ec, float sensitvity=0.05f);
		static void Control(SceneCamera& sc, float dt, float sensitivity=0.05f, float speed=1.0f);
	};
}