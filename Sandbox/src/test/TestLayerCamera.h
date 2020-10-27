#pragma once

#include "Gray/Layers/Layer.h"
#include "Platform/Opengl/Opengl.h"
#include "Platform/Opengl/test/Util.h"

#include "Gray/Graphics/Camera.h"

class TestLayerCamera : public Gray::Layer
{
public:
	void OnAttatch() override
	{
		Gray::Layer::Init();

		Gray::Util::sampleObject2(vb, ib1, va, shader);

		tex = new Gray::Texture("res/textures/t4.jpg", GL_RGB, GL_RGB);
		tex->Bind();

		shader->Bind();
		shader->SetUniform("tex1", 0);

		renderer = new Gray::Renderer();

		camera = new Gray::Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	}

	void OnDetatch() override
	{
		delete shader;
		delete vb;
		delete va;
		delete ib1;
		delete ib2;
		delete renderer;
	}

	void OnUpdate() override
	{
		Gray::Layer::OnUpdate();

		camera->OnUpdate(dt);

		shader->SetUniform("model", glm::mat4(1.0f));
		shader->SetUniform("view", camera->GetView());
		shader->SetUniform("projection",  camera->GetProjection());

		renderer->Clear();
		renderer->Draw(*va, *ib1, *shader);
	}

	Gray::Camera* GetCamera()
	{
		return camera;
	}

	void OnMouseMoved(Gray::MouseMovedEvent& e) override
	{
		camera->UpdateLook();
	}

	void OnKeyPressed(Gray::KeyPressedEvent& e) override
	{
		
	}

private:
	Gray::Shader* shader;
	Gray::VertexBuffer* vb;
	Gray::VertexArray* va;
	Gray::IndexBuffer* ib1;
	Gray::IndexBuffer* ib2;
	Gray::Texture* tex;
	Gray::Renderer* renderer;
	Gray::Camera* camera;

	const float dr = 0.01;
	float mX, mY;
};

