#include "grpch.h"
#include "Renderable.h"
#include "Uniforms/MaterialUMFactory.h"
#include "Uniforms/TransformUMFactory.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Gray
{
	const Renderer Renderable::renderer;

	Renderable::Renderable() : isRenderEnabled(true)
	{
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

	void Renderable::SetTransformUM(TransformUM tUM)
	{
		this->tUM = tUM;
	}

	void Renderable::SetMaterialUM(MaterialUM matUM)
	{
		this->matUM = matUM;
	}

}