#pragma once

#include "Test.h"

#include "Gray/Graphics/Scene.h"
#include "Gray/Graphics/Light/PointLight.h"
#include "Gray/Graphics/Source/CameraSource.h"
#include "Gray/Graphics/Model/RenderableModel.h"

#include "imgui.h"
#include "imguiFileChooser/ImGuiFileDialog.h"

#define RAND_FLOAT (float)rand() / RAND_MAX

namespace Test
{
	class TestModelLoading : public Test
	{
	public:
		TestModelLoading(int n=100, float closeness=10)
			: closeness(closeness), n(n), scene(Gray::Scene(1)), path("res/models/47-obj/Handgun_obj.obj")
		{
			
		}

		Gray::Scene* OnInit() override
		{
			glClearColor(0, 0, 0, 1);
			GRAY_INFO("Attampting to load " + path);
			scene.ClearScene();
			scene.SetCapacity(1);

			auto model = scene.CreateRenderModel();
			model->LoadModel(path, false);

			std::vector<float> offsets;
			offsets.reserve((3 * (size_t)n));

			offsets.push_back(0);
			offsets.push_back(0);
			offsets.push_back(0);
			for (int i = 0; i < 3 * n; i++)
			{
				float x = (n * RAND_FLOAT - n / 2) / closeness;
				offsets.push_back(x);
			}
			model->SetOffsets(std::move(offsets));

			auto source = std::make_unique<Gray::CameraSource>(scene.GetCamera());
			auto ls = scene.CreateLight(Gray::LightType::PointLight, std::move(source));
			ls->SetAttenuation(1.0f, 0, 0);

			return &scene;
		}

		void OnUpdate(float dt) override
		{
			
			for (auto& renderable : scene)
			{
				renderable.OnUpdate(dt);
			}
		}

		// Debug 

		void OnImguiRender(float dt)
		{
			DebugFileChooser();
			DebugNumberAndDensity();
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

		void DebugNumberAndDensity()
		{
			static bool changed = false;
			changed = ImGui::InputInt("Number of models", &n);
			changed |= ImGui::InputFloat("Closeness", &closeness);

			if (changed)
			{
				OnInit();
			}
		}

	private:
		Gray::Scene scene;

		float closeness;
		int n;
		std::string path;
	};

	
}