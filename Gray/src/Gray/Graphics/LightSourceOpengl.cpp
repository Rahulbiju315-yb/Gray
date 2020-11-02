#include "grpch.h"

#include "LightSourceOpengl.h"

#include "Gray/Application.h"
#include "Gray/Layers/RenderLayer.h"

#include "Platform/Opengl/test/Util.h"

namespace Gray
{
	Renderer* Renderable::renderer = nullptr;

	LightSourceOpengl::LightSourceOpengl(glm::vec3 color)
	{
		//NOTE :: TO BE REPLACED LATER WITH OPTIMISED CODE
		Util::sampleObject2(vb, ib, va, Renderable::shader, false);

		//Create shader
		shader = new Shader("res/shaders/lightCubeShader.shader");
		SetColor(color);

	}

	LightSourceOpengl::~LightSourceOpengl()
	{
	}

	void LightSourceOpengl::SetColor(glm::vec3 color)
	{
		this->color = color;
		shader->SetUniform("light", color);
	}

	const glm::vec3& LightSourceOpengl::GetColor()
	{
		return color;
	}


	void LightSourceOpengl::OnUpdate(float dt)
	{
		//More concise way to do error checking perhaps???

		if(renderer != nullptr)
			renderer->Draw(*va, *ib, *shader);
		else
		{
			GRAY_CORE_ERROR("Renderer not initialized");
		}
	}

	void LightSourceOpengl::OnImguiRender()
	{ 
		bool changed;

		glm::vec3 lightColor = GetColor();

		std::string lCol = "Light Color : " + std::to_string(lightColor.x) + ", " + std::to_string(lightColor.y) 
			+ ", " + std::to_string(lightColor.z);
		ImGui::Text(lCol.c_str());

		changed  = ImGui::Checkbox("Enable Light Cube", &isRenderEnabled);
		changed = ImGui::ColorEdit4("choose light color", &color.x);

		if (changed)
		{
			Application::GetApp()->GetRenderLayer()->SetForEachData((void*)&color);

			ForEachRenderableFunction changeLightColor = [](Renderable* r, void* data)
			{
				r->GetShader()->SetUniform("light", *(glm::vec3*)data);
			};

			Application::GetApp()->GetRenderLayer()->ForEach(changeLightColor);
		}
	}

}