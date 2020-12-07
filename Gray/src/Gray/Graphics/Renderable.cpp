#include "grpch.h"
#include "Renderable.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Gray
{
	const glm::mat4 Renderable::UNIT_MAT4(1.0f);
	const Renderer Renderable::renderer;

	void Renderable::SetRenderEnabled(bool en) 
	{
		isRenderEnabled = en; 
	}

	bool Renderable::GetRenderEnabled() const 
	{ 
		return isRenderEnabled; 
	}

	void Renderable::SetName(std::string name) 
	{ 
		this->name = name; 
	}

	const std::string& Renderable::GetName() const 
	{ 
		return name;
	}

	std::shared_ptr<Shader> Renderable::GetShader() 
	{ 
		return shader; 
	}

	void Renderable::SetShader(std::shared_ptr<Shader> shader) 
	{ 
		this->shader = shader; 
	}

	const glm::vec3& Renderable::GetPos() const
	{ 
		return pos; 
	}

	void Renderable::SetPos(glm::vec3 pos)
	{
		this->pos = pos;
		model = glm::scale(glm::translate(UNIT_MAT4, pos), scale);
	}
	
	const glm::vec3& Renderable::GetDir() const 
	{ 
		return dir;  
	} // NOTICEEEEE

	void Renderable::SetYawPitch(glm::vec2 yawPitch)
	{
		this->yawPitch = yawPitch;

		float yaw = glm::radians(yawPitch.x);
		float pitch = glm::radians(yawPitch.y);

		dir = glm::vec3(0); //WTH ???!!!
	}

	const Renderer* Renderable::GetRenderer()
	{
		return &renderer; 
	}

	void Renderable::SetMaterial(Material material)
	{
		this->material = material; 
	}

	const Material& Renderable::GetMaterial() const 
	{ 
		return material;
	}

	void Renderable::SetMaterialUM(MaterialUM materialUM)
	{
		materialUM.TieWith(this);
		this->materialUM = std::move(materialUM);
	}

	void Renderable::SetModelUM(ModelUM modelUM)
	{
		modelUM.TieWith(this);
		this->modelUM = std::move(modelUM);
	}

	const glm::mat4& Renderable::GetModel() const
	{
		return model;
	}

	void Renderable::SetModelUniforms() const
	{
		modelUM.SetUniformFor(*shader);
	}

	void Renderable::SetMaterialUniforms() const
	{
		materialUM.SetUniformFor(*shader);
	}

}