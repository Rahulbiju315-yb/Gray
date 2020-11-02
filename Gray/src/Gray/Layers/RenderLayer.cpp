#include "grpch.h"

#include "RenderLayer.h"

#include "Gray/Graphics/Renderable.h"
#include "imgui.h"

namespace Gray
{
	RenderLayer::RenderLayer()
	{
		data = nullptr;

		Renderer* renederer = new Renderer(); //TO be later done in renderable perhaps ??
		Renderable::SetRenderer(renederer);

		projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

		camera = new Camera(glm::vec3(0.0f));
		cameraLookEn = false;
		cameraMovEn = false;
		

		lightSource = new LightSourceOpengl(glm::vec3(1.0f, 1.0f, 1.0f));
		lightSource->SetPos(glm::vec3(1.0f, 0.0f, 5.0f));
		lightSource->GetShader()->SetUniform("projection", projection);
		lightSource->GetShader()->SetUniform("light", lightSource->GetColor());
		lightSource->SetRenderEnabled(true);

	}

	RenderLayer::~RenderLayer()
	{
		delete camera;
	}

	void RenderLayer::OnAttatch()
	{
		
	}

	void RenderLayer::OnDetatch()
	{
		
	}

	void RenderLayer::AddRenderable(Renderable* r)
	{
		r->GetShader()->SetUniform("materials.ambient", glm::vec3(0.1f));
		r->GetShader()->SetUniform("materials.specular", glm::vec3(0.5f));
		r->GetShader()->SetUniform("materials.diffuse", glm::vec3(1.0f));

		r->GetShader()->SetUniform("projection", projection);
		r->GetShader()->SetUniform("light", lightSource->GetColor()); 
		r->GetShader()->SetUniform("lightPos", lightSource->GetPos());
		r->GetShader()->SetUniform("invModel", glm::inverse(r->GetModel()));
		renderList.push_back(r);
	}

	void RenderLayer::RemoveRenderable(Renderable* r)
	{
		std::remove(renderList.begin(), renderList.end(), r);
	}

	Renderable* RenderLayer::RenderableAt(int i)
	{
		return renderList.at(i);
	}

	void RenderLayer::OnUpdate()
	{
		Layer::OnUpdate();

		Renderable::GetRenderer()->Clear();
		
		if(cameraMovEn)
			camera->OnUpdate(dt);

		if (lightSource->GetRenderEnabled())
		{
			lightSource->GetShader()->SetUniform("view", camera->GetView());
			lightSource->OnUpdate(dt);
		}

		for (Renderable* renderable : renderList)
		{
			if (renderable->GetRenderEnabled())
			{
				renderable->GetShader()->SetUniform("view", camera->GetView());
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
		static glm::vec3 color = lightSource->GetColor();
		static bool showLightCube = true;

		static bool sel = false;

		
		if (ImGui::Button("Demo"))
		{
			sel = !sel;
		}

		if (sel)
		{
			ImGui::ShowDemoWindow();
		}

		camera->OnImguiRender();
		ImGui::Checkbox("Enable Camera Look Around", &cameraLookEn);
		ImGui::Checkbox("Enable Camera Movement", &cameraMovEn);

		lightSource->OnImguiRender();

		for (Renderable* renderable : renderList)
		{
			renderable->OnImguiRender();
		}
	}

	void RenderLayer::OnMouseMoved(MouseMovedEvent& e)
	{
		if(cameraLookEn)
			camera->UpdateLook();
	}

	void RenderLayer::SetCameraPos(glm::vec3 pos)
	{
		camera->SetPos(pos);
	}

	const glm::vec3& RenderLayer::GetCameraPos()
	{
		return camera->GetPos();
	}

	void RenderLayer::SetCameraDir(glm::vec2 dir)
	{
		camera->SetDir(dir);
	}

	const glm::vec2& RenderLayer::GetCameraDir()
	{
		return camera->GetDir();
	}

	void RenderLayer::SetLightColor(glm::vec3 color)
	{
		lightSource->SetColor(color);
	}

	const glm::vec3& RenderLayer::GetLightColor()
	{
		return lightSource->GetColor();
	}

	void RenderLayer::ForEach(ForEachRenderableFunction func)
	{
		for (Renderable* renderable : renderList)
		{
			func(renderable, data);
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