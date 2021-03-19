#pragma once

#include "Test.h"
#include "Gray/Graphics/DebugCube.h"
#include "ImGuizmo/ImGuizmo.h"
#include "Gray/Camera/SceneCamera.h"

namespace Test
{
	class TestGizmo : public Test
	{
	public:
		TestGizmo()
			:cursorEn(true)
		{
			shader->LoadProgram("res/shaders/colorShader.shader");
			shader->SetUniform("projection", camera.GetProjection());
			shader->SetUniform("color", glm::vec3(0.4, 0.8, 0.6));
			
			//tex->Bind(1);
		}

		void OnInit() 
		{ 
		}

		void PreRender(float dt) override
		{
			
		}

		void Render(float dt)
		{
			if (!cursorEn)
			{
				Gray::CameraController::Control(camera, dt);
			}
			shader->Bind();
			shader->SetUniform("view", camera.GetView());
			debugCube.Render(*shader);
		}

		void PostRender(float dt) override
		{
			ImGuiIO& io = ImGui::GetIO();
			ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
			ImGuizmo::SetOrthographic(false);
			/*ImGuizmo::DrawGrid(&(camera.GetView()[0][0]), &(camera.GetProjection()[0][0]),
				&(glm::mat4(1)[0][0]), 100.f);*/
			ImGuizmo::Manipulate(&(camera.GetView()[0][0]), &(camera.GetProjection()[0][0]), ImGuizmo::ROTATE,
				ImGuizmo::WORLD, &(debugCube.model[0][0]), nullptr, nullptr, nullptr, nullptr);
		}

		void OnEvent(Gray::Event& e) override
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
		Gray::DebugCube debugCube;
		Gray::NoCopy<Gray::Shader> shader;
		bool cursorEn;
	};
}