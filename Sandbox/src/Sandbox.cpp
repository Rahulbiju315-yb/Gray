#include "grpch.h"

#include "Gray.h"
#include "Gray/Layers/RenderLayer.h"

#include "Platform/Opengl/test/Util.h"
#include "Platform/Opengl/Opengl.h"

#include "glm/glm.hpp"

#include "Gray/TempUtil.h"
#include "Gray/Events/Input.h"

#include "Gray/Events/KeyCodes.h"

#include "test/TestModelLoading.h"

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
		test = std::make_unique<Test::TestModelLoading>();
		scene = test->OnInit();
	}

	void OnImguiRender(float dt) override
	{
		static bool showLightCube = true;
		static bool changed;
		static glm::vec3 ambientStrength(0.2f);

		if (scene)
		{
			scene->GetCamera()->OnImguiRender();
		}
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

	void OnUpdate(float dt) override
	{
		Gray::Renderable::GetRenderer()->Clear();
		test->OnUpdate(dt);
	}

	void OnMouseMoved(Gray::MouseMovedEvent& e) override
	{
		if (scene)
			scene->GetCamera()->UpdateLook();
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