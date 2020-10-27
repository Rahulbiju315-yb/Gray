#pragma once



#include "Gray/Layers/Layer.h"

#include "Platform/Opengl/Opengl.h"
#include "Platform/Opengl/test/Util.h"

#include "Gray/Graphics/LightSourceOpengl.h"
#include "Gray/Graphics/Camera.h"

class TestLayerLightSource : public Gray::Layer
{
public:
	TestLayerLightSource()
	{

		Gray::Layer::Init();

		ls = new Gray::LightSourceOpengl();

		shader = ls->GetShader();
		shader->Bind();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		shader->SetUniform("model", model);

		glm::mat4 projection = 	glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
		shader->SetUniform("projection", projection);

		glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
		shader->SetUniform("color", color);
		shader->Unbind();

		renderer = new Gray::Renderer();
		Gray::Renderable::SetRenderer(renderer);

		camera = new Gray::Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	}

	void OnAttatch() override
	{
		
	}

	void OnUpdate() override
	{
		Gray::Layer::OnUpdate();

		camera->OnUpdate(dt);
		shader->SetUniform("view", camera->GetView());

		ls->OnUpdate(dt);
	}

	void OnDetatch() override
	{
	
	}

	void OnMouseMoved(Gray::MouseMovedEvent& me) override
	{
		camera->UpdateLook();
	}

private:
	Gray::LightSourceOpengl* ls;

	Gray::VertexBuffer* vb;
	Gray::VertexArray* va;
	Gray::IndexBuffer* ib;
	Gray::Texture* tex;
	Gray::Renderer* renderer;
	Gray::Shader* shader;
	Gray::Camera* camera;
};