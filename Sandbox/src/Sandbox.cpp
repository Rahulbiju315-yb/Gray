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
#include "test/TestModelLoading.h"
#include "test/TestCleanup.h"
#include "test/TestFrameBuffer.h"

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
		test = std::make_unique<Test::TestFrameBuffer>();
		scene = test->OnInit();
	}

	void OnUpdate() override
	{
		test->OnUpdate(GetDT());
	}

private:
	std::shared_ptr<Gray::Scene> scene;
	std::unique_ptr<Test::Test> test;
	bool cursorEn;

};

Gray::Application* Gray::CreateApplication()
{
	return new Sandbox();
}