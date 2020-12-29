#pragma once
#pragma once

#include "Test.h"
#include "Gray/Graphics/Materials.h"
#include "Platform/Opengl/Texture.h"
#include "Gray/Graphics/Scene.h"
#include "Gray/Graphics/Light/PointLight.h"
#include "Gray/Graphics/Source/SourceFactory.h"
#include "Platform/Opengl/Opengl.h"

namespace Test
{
	#define RAND_FLOAT (float)rand() / RAND_MAX
	class TestManyCubes : public Test
	{
	public:
		TestManyCubes(int n, float closeness=20.f) : n(n), closeness(closeness)
		{
			tex1.LoadTexture("res/textures/container2.png", GL_RGBA, GL_RGBA);
			tex2.LoadTexture("res/textures/container2spec.png", GL_RGBA, GL_RGBA);
			tex3.LoadTexture("res/textures/container2spec.png", GL_RGBA, GL_RGBA);
		}

		std::shared_ptr<Gray::Scene> OnInit() override
		{
			auto scene = std::make_shared<Gray::Scene>(n + 1);

			auto rModel = scene->CreateRenderModel();
			rModel->LoadTestCube();

			

			auto& material = rModel->begin()->GetMaterial();
			material.AddDiffuse(&tex1);
			material.AddSpecular(&tex2);

			for (int i = 0; i < n; i++)
			{
				auto dbc = scene->CreateRenderModel();
				dbc->LoadModel(rModel->GetShader(), rModel->begin()->GetRenderData());

				auto& material = dbc->begin()->GetMaterial();
				material.AddDiffuse(&tex1);
				material.AddSpecular(&tex2);

				float x = (n * RAND_FLOAT - n/2) / closeness;
				float y = (n * RAND_FLOAT - n/2) / closeness;
				float z = (n * RAND_FLOAT - n/2) / closeness;

				dbc->GetTransform().SetPos(glm::vec3(x, y, z));
			}

			auto source = std::make_unique<Gray::CameraSource>(scene->GetCamera());
			auto ls = scene->CreateLight(Gray::LightType::PointLight, std::move(source));
			ls->SetAttenuation(1.0f, 0.07f, 0.14f);

			rModel->GetShader()->SetUniform("projection", scene->GetCamera()->GetProjection());

			return scene;
		}

	private:
		int n;
		float closeness;

		Gray::Texture tex1, tex2, tex3;
	};
}