#include "grpch.h"
#include "Renderable.h"
#include "Gray/Application.h"
#include "imgui.h"

namespace Gray
{
	void Gray::Debug::StandardLightingDebug(Renderable* r)
	{
		Shader* shader = r->GetShader();

		static glm::vec3 ambientStrength(0.1f);
		static glm::vec3 specularStrength(0.1f);
		static glm::vec3 diffuseStrength(0.1f);

		RenderLayer* renderLayer = Application::GetApp()->GetRenderLayer();

		bool changed = ImGui::SliderFloat3("Change ambient strength", &ambientStrength.r, 0.0f, 1.0f);
		shader->SetUniform("material.ambient", ambientStrength);

		changed = ImGui::SliderFloat3("Change Specular strength", &specularStrength.r, 0.0f, 1.0f);
		shader->SetUniform("material.specular", specularStrength);

		changed = ImGui::SliderFloat3("Change Diffuse strength", &diffuseStrength.r, 0.0f, 1.0f);
		shader->SetUniform("material.diffuse", diffuseStrength);
	}
}