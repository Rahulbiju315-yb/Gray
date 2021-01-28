#pragma once

#include "Test.h"

#include "Gray/Graphics/Scene.h"
#include "Gray/Graphics/Light/PointLight.h"
#include "Gray/Graphics/Source/CameraSource.h"
#include "Gray/Graphics/Source/StaticSource.h"
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
		TestModelLoading(int n = 0, float closeness = 10)
			: closeness(closeness), n(n), path(BAG), rIndex(-1)
		{
			
		}

		
		Gray::Scene* OnInit() override
		{
		}

		void Render(float dt) override
		{

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

		void DebugReloadButtons()
		{
		}

	private:
		int rIndex;

		float closeness;
		int n;
		std::string path;
	};

	
}