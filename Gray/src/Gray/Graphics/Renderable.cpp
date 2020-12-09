#include "grpch.h"
#include "Renderable.h"
#include "Uniforms/MaterialUMFactory.h"
#include "Uniforms/ModelUMFactory.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Gray
{
	const Renderer Renderable::renderer;

	Renderable::Renderable() : isRenderEnabled(true)
	{
		SetModelUM(CreateModelUM(ModelUMType::SimpleModelUM));
		SetMaterialUM(CreateMaterialUM(MaterialUMType::SimpleMaterialUM));
	}

	Renderable::Renderable(RenderData renderData)
	{
		this->renderData = renderData;
	}

	void Renderable::SetRenderEnabled(bool en)
	{
		isRenderEnabled = en; 
	}

	bool Renderable::GetRenderEnabled() const 
	{ 
		return isRenderEnabled; 
	}

	std::shared_ptr<Shader> Renderable::GetShader() 
	{ 
		return shader; 
	}

	void Renderable::SetShader(std::shared_ptr<Shader> shader) 
	{ 
		this->shader = shader; 
	}

	const Renderer* Renderable::GetRenderer()
	{
		return &renderer; 
	}

	void Renderable::SetMaterial(Material material)
	{
		this->material = material; 
	}

	Material* Renderable::GetMaterial()
	{ 
		return &material;
	}

	void Renderable::SetMaterialUM(MaterialUM materialUM)
	{
		materialUM.TieWith(this);
		this->materialUM = materialUM;
	}

	void Renderable::SetModelUM(ModelUM modelUM)
	{
		modelUM.TieWith(this);
		this->modelUM = modelUM;
	}

	Model* Renderable::GetModel()
	{
		return &model;
	}

	RenderData Renderable::GetRenderData() const
	{
		return renderData;
	}

	void Renderable::SetRenderData(RenderData renderData)
	{
		this->renderData = renderData;
	}

	void Renderable::SetModelUniforms() const
	{
		modelUM.SetUniformFor(*shader);
	}

	void Renderable::SetMaterialUniforms() const
	{
		materialUM.SetUniformFor(*shader);
	}

	const ModelUM& Renderable::GetModelUM() const
	{
		return modelUM;
	}

	const MaterialUM& Renderable::GetMaterialUM() const
	{
		return materialUM;
	}

}