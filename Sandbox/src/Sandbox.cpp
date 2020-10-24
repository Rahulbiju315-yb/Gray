#include "Gray.h"
#include "grpch.h"

#include "Gray/Layers/ImguiLayer.h"

#include "Platform/Opengl/test/Util.h"
#include "Platform/Opengl/Opengl.h"

#include "glm/glm.hpp"

#include "Gray/TempUtil.h"

class TestLayer : public Gray::Layer
{
public:
	void OnAttatch() override
	{
		Gray::Layer::Init();

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
		Gray::Layer::OnUpdate();

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
			camera->UpdateDir((mXn - mX)/20.0f , 0.0f);
		}
		mX = mXn;
		mY = mYn;

		GRAY_INFO("New direction " + std::to_string(dir.x) + ", " + std::to_string(dir.y));
	}

	void OnKeyPressed(Gray::KeyPressedEvent& e) override
	{
		const glm::vec2& dir = camera->GetDir();
		const glm::vec3& pos = camera->GetPos();

		float yaw = glm::radians(dir.x);
		float pitch = glm::radians(dir.y);

		float k = dt * 0.01f;

		glm::vec3 x_ = k * glm::vec3(cos(yaw), sin(pitch), sin(yaw));
		glm::vec3 z_ = k * glm::vec3(-sin(yaw), sin(pitch), cos(yaw));

		if (e.GetKeyCode() == TO_INT(Gray::KeyCodes::Key_W))
		{
			camera->SetPos(pos - z_);
		}

		else if (e.GetKeyCode() == TO_INT(Gray::KeyCodes::Key_A))
		{
			camera->SetPos(pos - x_);
		}

		else if (e.GetKeyCode() == TO_INT(Gray::KeyCodes::Key_S))
		{
			camera->SetPos(pos + z_);
		}

		else if (e.GetKeyCode() == TO_INT(Gray::KeyCodes::Key_D))
		{
			camera->SetPos(pos + x_);
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

	const float dr = 0.01;
	float mX, mY;
};

class Sandbox : public Gray::Application
{
public:
	Sandbox()
	{
		Gray::TempUtil::DisableCursor();

		// Init
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//EndInit

		AddLayer(new TestLayer());
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