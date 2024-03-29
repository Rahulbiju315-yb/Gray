#pragma once

#include "Test.h"
#include "Gray/Graphics/Skybox.h"
#include "Gray/Camera/SceneCamera.h"
#include "Gray/Camera/CameraController.h"

namespace Test
{
	class TestSkybox : public Test
	{
	public:
		TestSkybox()
		{
			skybox.LoadSkybox("res/textures/skybox/", ".jpg");
			shader->LoadProgram("res/shaders/skyboxShader.shader");
			shader->SetUniform("projection", camera.GetProjection());
		}

		void OnInit() 
		{ 
		}

		void Render(float dt)
		{
			if (!cursorEn)
			{
				Gray::CameraController::Control(camera, dt);
			}
			skybox.RenderSkybox(camera.GetView(), *shader);
		}

		void PostRender(float dt) override
		{
		}

		void OnEvent(Gray::Event& e)
		{
			Gray::EventType type = e.GetType();
			if (type == Gray::EventType::KeyPressed)
				OnKeyPressed((Gray::KeyPressedEvent&)e);
		}

		void OnKeyPressed(Gray::KeyPressedEvent& e)
		{
			if (e.GetKeyCode() == GLFW_KEY_T)
			{
				Gray::Window::SetCursorEnabled(!Gray::Window::IsCursorEnabled());
			}
		}

	private:
		Gray::SceneCamera camera;
		Gray::Skybox skybox;
		Gray::NoCopy<Gray::Shader> shader;

		bool cursorEn;
	};
}