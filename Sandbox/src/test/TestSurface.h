#pragma once
#include "Test.h"
#include "Gray/Graphics/Surface.h"
#include "Gray/Graphics/Camera.h"
#include "Gray/Graphics/Source/CameraSource.h"
#include "Gray/Graphics/Source/StaticSource.h"
#include "glm/glm.hpp"
#include "Gray/TempUtil.h"
#include "Gray/Graphics/Skybox.h"

namespace Test
{
	const glm::mat4 model = glm::mat4(1);
	const glm::mat4 invModel = glm::inverse(model);

	class TestSurface : public Test
	{
	public:
		TestSurface()
		{
			// Skybox init
			skybox.LoadSkybox("res/textures/skybox/", ".jpg");
			skyboxShader->LoadProgram("res/shaders/skyboxShader.shader");
			skyboxShader->SetUniform("projection", camera.GetProjection());

			//Surface and surface shader init
			surface.GenerateUsingHMap(500, 500, 0.05f, "res/textures/t3spec.jpg");

			surfaceShader->LoadProgram("res/shaders/shader.shader");

			surfaceShader->SetUniform("model", model);
			surfaceShader->SetUniform("invModel", invModel);
			surfaceShader->SetUniform("projection", camera.GetProjection());

			//hMapTexture->LoadTexture("res/textures/t3spec.jpg", true);
			surfaceTexture->LoadTexture("res/textures/t1.jpg", false);

			surfaceShader->SetUniform("hMap", 1);
			surfaceShader->SetUniform("material.diffuse", 2);
			surfaceShader->SetUniform("material.specular", 3);
			surfaceShader->SetUniform("material.emission", 2);
			surfaceShader->SetUniform("material.ambient", 2);
			surfaceShader->SetUniform("material.shininess", 32.0f);


			Gray::Defaults::BlankTex()->Bind(3);
			hMapTexture->Bind(1);
			surfaceTexture->Bind(2);

			cursorEn = false;
			Gray::TempUtil::DisableCursor();


		}

		Gray::Scene* OnInit() override
		{
			return nullptr;
		}
		
		void Render(float dt) override
		{
			skybox.RenderSkybox(camera, *skyboxShader);

			surfaceShader->SetUniform("view", camera.GetView());
			surfaceShader->SetUniform("viewPos", camera.GetPos());

			if (!cursorEn)
			{
				camera.UpdateLook();
				camera.Move(dt);
			}

			surface.Render(*surfaceShader);
		}

		void PostRender(float dt) override
		{
			camera.PostRender();
		}

		void OnEvent(Gray::Event& e, Gray::EventType type)
		{
			if (type == Gray::EventType::KeyPressed)
				OnKeyPressed((Gray::KeyPressedEvent&)e);
		}

		void OnKeyPressed(Gray::KeyPressedEvent& e)
		{
			if (e.GetKeyCode() == TO_INT(Gray::KeyCodes::Key_T))
			{
				cursorEn = !cursorEn;
				if (cursorEn)
				{
					Gray::TempUtil::EnableCursor();
				}
				else
				{
					Gray::TempUtil::DisableCursor();
				}
			}
		}

	private:

		Gray::Camera camera;
		Gray::Surface surface;
		Gray::Skybox skybox;
		Gray::NoCopy<Gray::Shader> surfaceShader;
		Gray::NoCopy<Gray::Shader> skyboxShader;
		Gray::NoCopy<Gray::Texture> surfaceTexture;
		Gray::NoCopy<Gray::Texture> hMapTexture;
		bool cursorEn;
	};
}
