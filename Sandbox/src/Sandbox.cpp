#include "grpch.h"

#include "Gray.h"
#include "Gray/Layers/RenderLayer.h"

#include "Platform/Opengl/test/Util.h"
#include "Platform/Opengl/Opengl.h"

#include "glm/glm.hpp"

#include "Gray/TempUtil.h"
#include "Gray/Events/Input.h"

#include "Gray/Graphics/DebugCube.h"

#include "Gray/Events/KeyCodes.h"

#include "test/TestManyCubes.h"

#define RAND_FLOAT (float)rand() / RAND_MAX


class Sandbox : public Gray::Application
{
public:

	Sandbox() : cursorEn(true)
	{
		
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
		Test::TestManyCubes tmc(100, 10.0f);
		tmc.OnInit(renderLayer);
	}

private:
	bool cursorEn;
};

Gray::Application* Gray::CreateApplication()
{
	return new Sandbox();
}