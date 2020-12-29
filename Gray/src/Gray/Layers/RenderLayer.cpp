#include "grpch.h"

#include "RenderLayer.h"

#include "Gray/Graphics/Renderable.h"

#include "Gray/Graphics/Source/CameraSource.h"
#include "Gray/Graphics/Source/StaticSource.h"

#include "imgui.h"

namespace Gray
{
	static int countOpt = 1;
	static int countNonOpt = 1;
	
	int countSpot = 1;
	int countDir = 1;
	int countPoint = 1;

	RenderLayer::RenderLayer()
	{
	}

	void RenderLayer::SetScene(std::shared_ptr<Scene> scene)
	{
		this->scene = scene;
	}

	RenderLayer::RenderLayer(std::shared_ptr<Scene> scene) : scene(scene)
	{
	}

	void RenderLayer::OnAttatch()
	{
	}

	void RenderLayer::OnDetatch()
	{
	}

	void RenderLayer::OnUpdate()
	{
		Layer::OnUpdate();

		Renderable::GetRenderer()->Clear();

		if (scene)
		{
			scene->ComputeShaderSet();
			scene->GetCamera()->OnUpdate(dt);

			scene->SetProjectionUniform();
			scene->SetViewUniform();

			scene->LightUpScene();

			for (auto& renderable : *scene)
			{
				if (renderable.GetRenderEnabled())
				{
					renderable.OnUpdate(dt);
				}
			}
		}
		else
		{
			GRAY_WARN("Empty Scene");
		}
	}

	void RenderLayer::OnImguiRender()
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

	void RenderLayer::OnMouseMoved(MouseMovedEvent& e)
	{
		if(scene)
			scene->GetCamera()->UpdateLook();
	}

}