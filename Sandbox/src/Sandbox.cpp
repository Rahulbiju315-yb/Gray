#include "Gray.h"
#include "grpch.h"

#include "Gray/Layers/ImguiLayer.h"
#include "Gray/Layers/RenderLayer.h"

#include "Platform/Opengl/test/Util.h"
#include "Platform/Opengl/Opengl.h"

#include "glm/glm.hpp"

#include "Gray/TempUtil.h"
#include "Gray/Events/Input.h"

#include "imgui.h"
#include "test/TestLayerCamera.h"
#include "test/TestLayerLightSource.h"

#include "Gray/Graphics/Camera.h"
#include "Gray/Graphics/DebugCube.h"

#include "Gray/Events/KeyCodes.h"

//TO-DO
//=> Remove inheritance of layer by ImguiLayer ??
//=> Lighting
//=> Joystick support
//=> CODE CLEAN-UP ->> IMP!!!! EMERGENCY!!! CLEAN UP INCLUDES THEY ARE HELLA MESSY

class Sandbox : public Gray::Application
{
public:
	Sandbox()
	{
		// Init
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//EndInit

	}

	~Sandbox()
	{

	}

	void OnKeyPressed(Gray::KeyPressedEvent& e) override
	{
		if (e.GetKeyCode() == TO_INT(Gray::KeyCodes::Key_T))
		{
			cursorEn = !cursorEn;
			if (cursorEn)
			{
				Gray::TempUtil::EnableCursor();
				renderLayer->SetCameraLookAroundEnabled(false);
				renderLayer->SetCameraMovementEnabled(false);
			}
			else
			{
				Gray::TempUtil::DisableCursor();
				renderLayer->SetCameraLookAroundEnabled(true);
				renderLayer->SetCameraMovementEnabled(true);
			}
		};
	}

	void Init() override
	{
		Gray::Application::Init(); //Should probably be managed by Gray, rather then client

		Gray::DebugCube* dbc = new Gray::DebugCube(true);
		dbc->SetRenderEnabled(true);

		renderLayer->SetCameraLookAroundEnabled(true);
		renderLayer->SetCameraMovementEnabled(true);
		renderLayer->SetCameraPos(glm::vec3(0.0f, 0.0f, 3.0f));
		renderLayer->AddRenderable(dbc);
	}

private:
	bool cursorEn;
};

Gray::Application* Gray::CreateApplication()
{
	return new Sandbox();
}