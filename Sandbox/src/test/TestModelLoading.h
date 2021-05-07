#pragma once

#include "Test.h"

#include "Gray/Graphics/Light/PointLight.h"
#include "Gray/Graphics/Model/RenderableModel.h"
#include "Gray/Resources/ModelManager.h"

#include "Gray/Camera/SceneCamera.h"
#include "Gray/Camera/CameraController.h"

#include "imgui.h"
#include "imguiFileChooser/ImGuiFileDialog.h"
#include "Gray/Graphics/Light/LightingManager.h"
#include <utility>

#define RAND_FLOAT (float)rand() / RAND_MAX

namespace Test
{
	class TestModelLoading : public Test
	{
	public:
		TestModelLoading(int n = 0, float closeness = 10)
			: closeness(closeness), n(n), path(BAG), index(0)
		{
		}

		
		void OnInit() override
		{
			index = mm.GetModelId("res/models/backpack/backpack.obj");
			shader->LoadProgram("res/shaders/shader.shader");
			shader->SetUniform("projection", camera.GetProjection());

			Gray::PointLight pl;
			pl.attenuation = glm::vec3{1, 0, 0};
			pl.color.ambient = glm::vec3{ 1, 1, 1 };
			lm.AddPointLight(pl);
		}

		void PreRender(float dt) override
		{
			if (!Gray::Window::IsCursorEnabled())
			{
				Gray::CameraController::Control(camera, dt);
			}
		}

		void Render(float dt) override
		{
			if (mm.RequireInit())
			{
				mm.InitModels();
				if (!mm.RequireInit())
				{
					model = mm.GetModels(std::vector{ index })[0];
					rmodel.SetModel(model);
				}
			}
			else
			{
				lm.SetUniformsFor(*shader);
				shader->SetUniform("view", camera.GetView());
				rmodel.Render(*shader);
			}
		}

		// Debug 
		void PostRender(float dt)
		{

		}

		void DebugFileChooser()
		{
			if (ImGui::Button("Open File Dialog"))
				igfd::ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", "{.obj}", ".");

			if (igfd::ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey"))
			{
				if (igfd::ImGuiFileDialog::Instance()->IsOk)
				{
					path = igfd::ImGuiFileDialog::Instance()->GetFilePathName();
					std::replace(path.begin(), path.end(),'\\', '/');
					OnInit();
					GRAY_CORE_WARN(path);
				}

				igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");
			}
		}

		void OnEvent(Gray::Event& e)
		{
			if (e.GetType() == Gray::EventType::KeyPressed)
			{
				if (static_cast<Gray::KeyPressedEvent&>(e).GetKeyCode() == GLFW_KEY_T)
				{
					Gray::Window::SetCursorEnabled(!Gray::Window::IsCursorEnabled());
				}
			}
		}

		void DebugReloadButtons()
		{
		}

	private:
		Gray::SceneCamera camera;
		Gray::ModelManager mm;
		Gray::LightingManager lm;
		Gray::Model model;
		Gray::RenderableModel rmodel;
		Gray::NoCopy<Gray::Shader> shader;

		float closeness;
		int n;
		uint index;
		std::string path;
	};

	
}