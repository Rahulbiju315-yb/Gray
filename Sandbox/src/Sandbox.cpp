#include "grpch.h"

#include "Gray/Application.h"

#include "glm/glm.hpp"

#include "Gray/TempUtil.h"
#include "Gray/Events/Input.h"

#include "Gray/Events/KeyCodes.h"
#include "Gray/Debug.h"
#include "Platform/Opengl/Renderer.h"
#include "test/AllTests.h"

#define RAND_FLOAT (float)rand() / RAND_MAX

// TO - DO  -> LightSource from inheritance to composition

class Sandbox : public Gray::Application, public Gray::EventListener
{
public:
	Sandbox() : cursorEn(true), render(false)
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

		test = std::make_unique<Test::TestTexture>();
		test->OnInit();
	}

	void PreRender(float dt) override
	{
		test->PreRender(dt);
	}

	

	void Render(float dt) override
	{
		test->Render(dt);
	}

	void PostRender(float dt) override
	{
		Gray::FPSDebugInfo(dt);
		test->PostRender(dt);
	}

	void OnEvent(Gray::Event& e, Gray::EventType type) override
	{
		if (type == Gray::EventType::KeyPressed)
			OnKeyPressed((Gray::KeyPressedEvent&)e);

		test->OnEvent(e, type);
	}

	void OnKeyPressed(Gray::KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == TO_INT(Gray::KeyCodes::Key_T))
		{
			cursorEn = !cursorEn;
			if (cursorEn)
			{
				Gray::TempUtil::EnableCursor();
			}
			else
			{
				Gray::TempUtil::DisableCursor();
			}
		}
	}

private:
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
