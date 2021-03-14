#include "grpch.h"

#include "Gray/Application.h"

#include "glm/glm.hpp"

#include "Gray/TempUtil.h"
#include "Gray/Events/Input.h"

#include "Gray/Debug.h"
#include "Platform/Opengl/Renderer.h"
#include "test/AllTests.h"

#define RAND_FLOAT (float)rand() / RAND_MAX

class Sandbox : public Gray::Application, public Gray::EventListener
{
public:
	Sandbox() : render(false)
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
		if (e.GetKeyCode() == GLFW_KEY_T)
		{
			if (!Gray::TempUtil::IsCursorEnabled())
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
	bool render;
};

int main(int argc, char** argv)
{
	Sandbox app;
	app.Run();
	return 0;
}
