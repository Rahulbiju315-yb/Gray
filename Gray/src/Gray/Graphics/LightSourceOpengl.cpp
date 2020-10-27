#include "grpch.h"
#include "LightSourceOpengl.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Gray
{
	Renderer* Renderable::renderer = nullptr;

	LightSourceOpengl::LightSourceOpengl(glm::vec4 color)
	{
		this->color = color;

		//NOTE :: TO BE REPLACED LATER WITH OPTIMISED CODE

		Util::sampleObject2(vb, ib, va, shader, false);

		//Create shader
		shader = new Shader("res/shaders/lightCubeShader.shader");
		shader->Bind();
		shader->SetUniform("color", color);
		//SetPos(glm::vec3(0.0f, 0.0f, 3.0f));
	}

	LightSourceOpengl::~LightSourceOpengl()
	{
	}

	void LightSourceOpengl::SetColor(glm::vec4 color)
	{
		this->color = color;

		shader->Bind();
		shader->SetUniform("color", glm::vec4(color));

	}

	const glm::vec4& LightSourceOpengl::GetColor()
	{
		return color;
	}

	void LightSourceOpengl::SetPos(glm::vec3 pos)
	{
		this->pos = pos;
		model = glm::translate(glm::mat4(1.0f), pos);

		shader->Bind();
		shader->SetUniform("model", model);
	}

	const glm::vec3& LightSourceOpengl::GetPos(glm::vec3 pos)
	{
		return pos;
	}

	void LightSourceOpengl::OnUpdate(float dt)
	{
		renderer->Clear();
		renderer->Draw(*va, *ib, *shader);
	}

	Shader* LightSourceOpengl::GetShader()
	{
		return shader;
	}
}