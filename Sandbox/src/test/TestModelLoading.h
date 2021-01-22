#pragma once

#include "Test.h"

#include "Gray/Graphics/Scene.h"
#include "Gray/Graphics/Light/PointLight.h"
#include "Gray/Graphics/Source/CameraSource.h"
#include "Gray/Graphics/Model/RenderableModel.h"

#include "imgui.h"
#include "imguiFileChooser/ImGuiFileDialog.h"
#include "Gray/Graphics/Resource/ResourceManager.h"

#define RAND_FLOAT (float)rand() / RAND_MAX

namespace Test
{
	class TestModelLoading : public Test
	{
	public:
		TestModelLoading(int n = 100, float closeness = 10)
			: closeness(closeness), n(n), scene(Gray::Scene(1)), path(BAG), rIndex(-1)
		{
			
		}

		
		Gray::Scene* OnInit() override
		{
			glClearColor(0, 0, 0, 1);
			scene.ClearScene();
			scene.SetCapacity(1);

			rIndex = scene.CreateRModel();
			scene.SetModelPath(rIndex, path);

			Gray::RenderableModel& rmodel = scene.GetRModel(rIndex);
			auto source = std::make_unique<Gray::CameraSource>(&scene.GetCamera());
			int index = scene.CreateLight(Gray::LightType::PointLight, std::move(source));
			scene.GetLight(index, Gray::LightType::PointLight).SetAttenuation(1.0f, 0, 0);

			scene.InitForRender();
			scene.ReloadRModels(*this);
			return &scene;
		}

		void OnLoad(Gray::RenderableModel& model, int rindex)
		{
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
			scene.GetRModel(rIndex).SetInstanceOffsets(offsets);
		}

		void OnUpdate(float dt) override
		{
			if (scene.IsSceneComplete())
			{
				scene.RenderModels();
			}
			else
			{
				scene.LoadResources(*this);
			}
		}

		

		// Debug 

		void OnImguiRender(float dt)
		{
			DebugFileChooser();
			DebugNumberAndDensity();
			DebugReloadButtons();
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
			changed = ImGui::InputInt("Number of models", &n) && n <= 1000;
			

			changed |= ImGui::InputFloat("Closeness", &closeness);

			if (changed)
			{
				OnInit();
			}
		}

		void DebugReloadButtons()
		{
			static bool pressed = false;

			pressed = ImGui::Button("Reload Scene");
			if (pressed)
				OnInit();

			pressed = ImGui::Button("Reload resource");
			if (pressed)
			{
				for (int i = 0; i < 5; i++)
				{
					//Gray::ReloadModel(path, true);
					Gray::RMReloadShaders();
					OnInit();
				}
			}
		}
	private:
		Gray::Scene scene;
		int rIndex;

		float closeness;
		int n;
		std::string path;
	};

	
}