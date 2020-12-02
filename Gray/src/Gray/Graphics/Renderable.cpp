#include "grpch.h"
#include "Renderable.h"

namespace Gray
{
	const glm::mat4 Renderable::UNIT_MAT4(1.0f);
	const Renderer Renderable::renderer;

	void Renderable::SetRenderEnabled(bool en) { isRenderEnabled = en; }
	bool Renderable::GetRenderEnabled() { return isRenderEnabled; }

	void Renderable::SetName(std::string name) { this->name = name; }
	const std::string& Renderable::GetName() { return name; }

	std::shared_ptr<Shader> Renderable::GetShader() { return shader; }

	void Renderable::SetShader(std::shared_ptr<Shader> shader) { this->shader = shader; }

	const glm::vec3& Renderable::GetPos() { return pos; }

	void Renderable::SetPos(glm::vec3 pos)
	{
		this->pos = pos;
		//model = glm::scale(glm::translate(UNIT_MAT4, pos), scale);
	}
	
	const glm::vec3& Renderable::GetDir()
	{
		return glm::vec3(0);
	}

	void Renderable::SetYawPitch(glm::vec2 yawPitch)
	{
		this->yawPitch = yawPitch;

		float yaw = glm::radians(yawPitch.x);
		float pitch = glm::radians(yawPitch.y);

		dir = glm::vec3(0);
	}

	const Renderer* Renderable::GetRenderer() { return &renderer; }

	void Renderable::SetMaterial(Material material) { this->material = material; }
	Material* Renderable::GetMaterial() { return &material; }

	void Renderable::SetModelUniforms()
	{
		glm::mat4 model = glm::scale(glm::translate(UNIT_MAT4, pos), scale);
		shader->SetUniform("model", model);
		shader->SetUniform("invModel", glm::inverse(model));
	}

	void Renderable::SetMaterialUniforms()
	{

		shader->SetUniform("material.diffuse", 0);
		shader->SetUniform("material.specular", 1);
		shader->SetUniform("material.emission", 2);

		material.GetDiffuse()->Bind(0);
		material.GetSpecular()->Bind(1);
		material.GetEmission()->Bind(2);

		shader->SetUniform("material.shininess", material.GetShininess());
	}

}