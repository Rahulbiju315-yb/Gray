#include "grpch.h"

#include "RenderLayer.h"

#include "Gray/Graphics/Renderable.h"
#include "imgui.h"

namespace Gray
{
	static int countOpt = 1;
	static int countNonOpt = 1;

	RenderLayer::RenderLayer() : 
		cameraLookEn(false), cameraMovEn(false), 
		projection(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f)),
		camera(this), data(nullptr)
	{
		// -- code that must setup lighting for any given scene
		lightSources.push_back(std::make_shared<PointLight>(LightColor(), Defaults::ORIGIN));
		lightSources.push_back(std::make_shared<DirectionalLight>(LightColor(), glm::vec3(1.0f, 0.0f, 0.0f)));
		lightSources.push_back(std::make_shared<SpotLight>(LightColor(), Defaults::ORIGIN, 
			glm::vec3(1.0f, 0.0f, 0.0f)));
		// --
	}

	RenderLayer::~RenderLayer()
	{
	}

	void RenderLayer::OnAttatch()
	{
	}

	void RenderLayer::OnDetatch()
	{
	}

	void RenderLayer::AddRenderable(std::shared_ptr<Renderable> r)
	{
		r->GetShader()->SetUniform("projection", projection);
		unique_shaders.insert(r->GetShader().get());
		renderList.push_back(r);
	}

	void RenderLayer::RemoveRenderable(std::shared_ptr<Renderable> r)
	{
		renderList.erase(std::remove(renderList.begin(), renderList.end(), r), renderList.end());
	}

	std::shared_ptr<Renderable> RenderLayer::RenderableAt(int i)
	{
		return renderList.at(i);
	}

	void RenderLayer::OnUpdate()
	{
		Layer::OnUpdate();

		static bool changed;

		Renderable::GetRenderer()->Clear();
		
		if(cameraMovEn)
			camera.OnUpdate(dt);

		for (auto lightSource : lightSources)
		{
			int pointCount = 0, spotCount = 0;

			for (auto shader : unique_shaders)
			{
				if (shader != nullptr)
				{
					lightSource->SetUniformFor(shader);
				}
			}
		}

		for (auto shader : unique_shaders)
		{	
			/*if(shader)
				shader->SetUniform("view", camera.GetView()); */

			// Is this opt really necessary ???
			// For setting the view matrix, this has hardly a performance improvement , even while 
			// rendering 10000 cubes. 
		}

		for (auto renderable : renderList)
		{
			if (renderable->GetRenderEnabled())
			{
				renderable->GetShader()->SetUniform("view", camera.GetView());
				renderable->SetUniforms();
				renderable->OnUpdate(dt);
			}
		}
	}

	void RenderLayer::SetCameraMovementEnabled(bool en)
	{
		cameraMovEn = en;
	}

	bool RenderLayer::GetCameraMovementEnabled()
	{
		return cameraLookEn;
	}

	void RenderLayer::SetCameraLookAroundEnabled(bool en)
	{
		cameraLookEn = en;
	}

	bool RenderLayer::GetCameraLookAroundEnabled()
	{
		return cameraLookEn;
	}

	void RenderLayer::OnImguiRender()
	{
		static bool showLightCube = true;
		static bool changed;
		static glm::vec3 ambientStrength(0.2f);

		camera.OnImguiRender();

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
		ImGui::Checkbox("Enable Camera Look Around", &cameraLookEn);
		ImGui::Checkbox("Enable Camera Movement", &cameraMovEn);


		for (std::shared_ptr<Renderable> renderable : renderList)
		{
			if(ImGui::CollapsingHeader(renderable->GetName().c_str()))
				renderable->OnImguiRender();
		}
	}

	void RenderLayer::OnMouseMoved(MouseMovedEvent& e)
	{
		if(cameraLookEn)
			camera.UpdateLook();
	}

	void RenderLayer::SetCameraPos(glm::vec3 pos)
	{
		camera.SetPos(pos);
	}

	const glm::vec3& RenderLayer::GetCameraPos()
	{
		return camera.GetPos();
	}

	void RenderLayer::SetCameraDir(glm::vec2 dir)
	{
		camera.SetDir(dir);
	}

	const glm::vec2& RenderLayer::GetCameraDir()
	{
		return camera.GetDir();
	}

	void RenderLayer::ForEach(ForEachRenderableFunction func)
	{
		for (auto renderable : renderList)
		{
			func(renderable.get(), data);
		}
	}

	void RenderLayer::SetForEachData(void* data)
	{
		this->data = data;
	}

	void* RenderLayer::GetForEachData()
	{
		return data;
	}
}