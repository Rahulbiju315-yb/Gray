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
#include "test/TestMemory.h"

#define RAND_FLOAT (float)rand() / RAND_MAX

// TO - DO  -> LightSource from inheritance to composition

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
			if (scene)
			{
				cursorEn = !cursorEn;
				if (cursorEn)
				{
					Gray::TempUtil::EnableCursor();
					scene->GetCamera()->SetLookAroundEnabled(false);
					scene->GetCamera()->SetMoveEnabled(false);
				}
				else
				{
					Gray::TempUtil::DisableCursor();
					scene->GetCamera()->SetLookAroundEnabled(true);
					scene->GetCamera()->SetMoveEnabled(true);
				}
			}
		};
	}

	void Init() override
	{
		/*AddLayer(&renderLayer);*/
		Test::TestManyCubes tmc(10000, 50.0f);
		scene = tmc.OnInit(&renderLayer);
	}

private:
	bool cursorEn;
	Gray::RenderLayer renderLayer;
	std::shared_ptr<Gray::Scene> scene;

};

Gray::Application* Gray::CreateApplication()
{
	return new Sandbox();
}