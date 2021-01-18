#include "grpch.h"

#include "Gray/Application.h"

#include "glm/glm.hpp"

#include "Gray/TempUtil.h"
#include "Gray/Events/Input.h"

#include "Gray/Events/KeyCodes.h"
#include "Gray/Debug.h"

#include "test/AllTests.h"

#define RAND_FLOAT (float)rand() / RAND_MAX

// TO - DO  -> LightSource from inheritance to composition

class Sandbox : public Gray::Application, public Gray::EventListener
{
public:
	Sandbox() : cursorEn(true), render(false), scene(nullptr)
	{
		Gray::Window::GetWindow()->AddListener(this);
	}

	~Sandbox()
	{

	}

	void OnInit() override
	{
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		test = std::make_unique<Test::TestModelLoading>();
		scene = test->OnInit();
	}

	void OnImguiRender(float dt) override
	{
		if (scene)
		{
			scene->GetCamera()->OnImguiRender();
		}

		Gray::FPSDebugInfo(dt);
		test->OnImguiRender(dt);
	}

	void OnUpdate(float dt) override
	{
		scene->ComputeShaderSet();
		scene->SetViewUniform();
		scene->SetProjectionUniform();
		scene->LightUpScene();
		scene->GetCamera()->OnUpdate(dt);

		Gray::Renderable::GetRenderer()->Clear();
		test->OnUpdate(dt);
	}

	void OnEvent(Gray::Event& e, Gray::EventType type) override
	{
		if (type == Gray::EventType::KeyPressed)
			OnKeyPressed((Gray::KeyPressedEvent&)e);

		else if (type == Gray::EventType::MouseMoved)
			OnMouseMoved((Gray::MouseMovedEvent&)e);
	}

	void OnKeyPressed(Gray::KeyPressedEvent& e)
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
		}
	}

	void OnMouseMoved(Gray::MouseMovedEvent& e)
	{
		if (scene)
			scene->GetCamera()->UpdateLook();
	}

private:
	Gray::Scene* scene;
	std::unique_ptr<Test::Test> test;
	
	bool cursorEn;
	bool render;
};

int main(int argc, char** argv)
{
	Sandbox app;
	app.Run();
	return 0;
}
