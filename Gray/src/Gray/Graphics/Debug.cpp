#include "grpch.h"
#include "Renderable.h"
#include "imgui.h"
#include "Defaults.h"

namespace Gray
{
	void Gray::Debug::StandardLightingDebug(Renderable* r)
	{
		auto shader = (r->GetShader());
		bool changed;

		float shininess = r->GetMaterial()->GetShininess();
		
		changed = ImGui::SliderFloat(("Change Shininess ##" + r->GetName()).c_str(), &shininess, 0.0f, 128.0f);
		if (changed)
		{
			shader->SetUniform("material.shininiess", shininess);
			r->GetMaterial()->SetShininess(shininess);
		}
	}
}