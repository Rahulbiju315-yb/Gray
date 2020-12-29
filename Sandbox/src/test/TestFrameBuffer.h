#pragma once

#include "Test.h"
#include "Platform/Opengl/FrameBuffer.h"
#include "Platform/Opengl/BufferLayout.h"
#include "Gray/Application.h"

namespace Test
{
	class TestFrameBuffer : public Test
	{
	public:
		TestFrameBuffer()
		{
			tex1.LoadTexture("res/textures/container2.png", GL_RGBA, GL_RGBA);
			tex2.LoadTexture("res/textures/container2spec.png", GL_RGBA, GL_RGBA);

			int width = 1200, height = 700;
			tex3.LoadEmptyTexture(width, height);
		}

		std::shared_ptr<Gray::Scene> OnInit()
		{
			scene = std::make_shared<Gray::Scene>(1);

			auto cube = scene->CreateRenderModel(); // Cube to render
			cube->LoadTestCube(true);
			auto& material = (cube->begin())->GetMaterial();
			material.AddDiffuse(&tex1);
			material.AddSpecular(&tex2);

			auto source = std::make_unique<Gray::CameraSource>(scene->GetCamera()); // Lighting for scene
			auto ls = scene->CreateLight(Gray::LightType::PointLight, std::move(source));
			ls->SetAttenuation(1.0f, 0.07f, 0.14f);
			
			//Shader for on-screen rendering
			auto shader = std::make_shared<Gray::Shader>("res/shaders/textureShader.shader");

			 // Quad to render offscreen render result
			float vertices[] =
			{
				-1.0f,  1.0f,  0.0f, 1.0f,
				-1.0f, -1.0f,  0.0f, 0.0f,
				1.0f, -1.0f,  1.0f, 0.0f,

				-1.0f,  1.0f,  0.0f, 1.0f,
				1.0f, -1.0f,  1.0f, 0.0f,
				1.0f,  1.0f,  1.0f, 1.0
			};
			unsigned int indices[] =
			{
				0, 1, 2, 3, 4, 5
			};
			auto mesh = square.AddMesh();
			Gray::BufferLayout layout;
			layout.Push<float>(2);
			layout.Push<float>(2);
			mesh->SetupMesh(vertices, 24, indices, 6, layout);
			mesh->GetMaterial().AddEmission(&tex3);
			square.SetShader(shader);

			//Uniform setter for square
			Gray::UniformSetter setter = [](const Gray::Shader& shader, Gray::RenderableModel& model)
			{
				auto& material = model.begin()->GetMaterial();
				(material.GetEmissionMaps())[0]->Bind(0);
				shader.SetUniform("tex", 0);
			};
			square.SetUniformSetter(setter);

			fb.AddAttachment(tex3, Gray::AttachmentType::Color);
			GRAY_INFO("Is FB complete : " + std::to_string(fb.IsComplete()));
	
			return scene;
		}
		
		void OnUpdate(float dt) override
		{
			//render to offscreen framebuffer
			fb.Bind();

			scene->ComputeShaderSet();
			scene->SetViewUniform();
			scene->SetProjectionUniform();
			scene->LightUpScene();
			for (auto& r : *scene)
			{
				r.OnUpdate(dt);
			}

			fb.Unbind();
			
			//Render result to screen

			square.OnUpdate(dt);
		}

	private:
		Gray::Texture tex1, tex2, tex3;
		std::shared_ptr<Gray::Scene> scene;
		Gray::RenderableModel square;
		Gray::FrameBuffer fb;
	};
}