#include "Gray.h"
#include "grpch.h"

#include "Gray/Layers/ImguiLayer.h"


#include "Platform/Opengl/test/Util.h"
#include "Platform/Opengl/Opengl.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"

class TestLayer : public Gray::Layer
{
public:
	void OnAttatch() override
	{
		Gray::Util::sampleObject2(vb, ib1, ib2, va, shader);

		tex = new Gray::Texture("res/textures/t4.jpg", GL_RGB, GL_RGB);
		tex->bind();

		shader->bind();
		shader->setUniform("tex1", 0);

		renderer = new Gray::Renderer();

		camera = new Gray::Camera(glm::vec3(0.0f, 0.0f, 3.0f));

		mX = -1;
		mY = -1;
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
		shader->setUniform("model", glm::mat4(1.0f));
		shader->setUniform("view", camera->GetView());

		shader->setUniform("projection",  camera->GetProjection());

		renderer->clear();
		renderer->draw(*va, *ib1, *shader);
	}

	void OnMouseMoved(Gray::MouseMovedEvent& e) override
	{
		const glm::vec2& dir = camera->GetDir();
		
		float mXn = e.GetX();
		float mYn = e.GetY();

		if (mX == -1)
		{
			mX = mXn;
			mY = mYn;
		}
		else
		{
			camera->SetDir(dir.x + (mXn - mX)/20.0f , dir.y);
		}
		mX = mXn;
		mY = mYn;
	}

	void OnKeyPressed(Gray::KeyPressedEvent& e) override
	{
		GRAY_INFO("Key pressed event handled");
		if (e.GetKeyCode() == Gray::KeyCodes::Key_W)
		{
			const glm::vec3& pos = camera->GetPos();
			camera->SetPos(pos.x, pos.y, pos.z - dr);
		}

		else if (e.GetKeyCode() == Gray::KeyCodes::Key_A)
		{
			const glm::vec3& pos = camera->GetPos();
			camera->SetPos(pos.x - dr, pos.y, pos.z);
		}

		else if (e.GetKeyCode() == Gray::KeyCodes::Key_S)
		{
			const glm::vec3& pos = camera->GetPos();
			camera->SetPos(pos.x, pos.y, pos.z + dr);
		}

		else if (e.GetKeyCode() == Gray::KeyCodes::Key_D)
		{
			const glm::vec3& pos = camera->GetPos();
			camera->SetPos(pos.x + dr, pos.y, pos.z);
		}

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

	const float dr = 0.1;
	float mX, mY;
};

class Sandbox : public Gray::Application
{
public:
	Sandbox()
	{

		AddLayer(new TestLayer());

		// Init
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//EndInit
	}

	~Sandbox()
	{

	}

	void OnMouseDragged(Gray::MouseDraggedEvent& e) override
	{
		GRAY_INFO("Mouse Dragged Event OK");
	}

	void OnMousePressed(Gray::MousePressedEvent& e) override
	{
		GRAY_INFO("Mouse Pressed Event OK");
	}
};

Gray::Application* Gray::CreateApplication()
{
	return new Sandbox();
}