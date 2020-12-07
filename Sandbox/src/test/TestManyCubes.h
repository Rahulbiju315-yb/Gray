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
			
		}

		std::shared_ptr<Gray::Scene> OnInit(Gray::RenderLayer* renderLayer) override
		{
			std::shared_ptr<Gray::Scene> scene = std::make_shared<Gray::Scene>();

			std::shared_ptr<Gray::DebugCube> dbcRoot = std::make_shared<Gray::DebugCube>(true);
			dbcRoot->SetRenderEnabled(true);

			Gray::Texture tex;
			tex.LoadTexture("res/textures/container2.png", GL_RGBA, GL_RGBA);

			Gray::Texture tex2;
			tex2.LoadTexture("res/textures/container2spec.png", GL_RGBA, GL_RGBA);

			Gray::Texture tex3;
			tex3.LoadTexture("res/textures/container2spec.png", GL_RGBA, GL_RGBA);

			Gray::Material material = dbcRoot->GetMaterial();
			material.SetDiffuse(tex);
			material.SetSpecular(tex2);

			for (int i = 0; i < n; i++)
			{
				//std::shared_ptr<Gray::DebugCube> dbc = std::make_shared<Gray::DebugCube>(false, dbcRoot->GetShader());
				std::shared_ptr<Gray::DebugCube> dbc = std::make_shared<Gray::DebugCube>(*dbcRoot);

				float x = (n * RAND_FLOAT - n/2) / closeness;
				float y = (n * RAND_FLOAT - n/2) / closeness;
				float z = (n * RAND_FLOAT - n/2) / closeness;

				dbc->SetPos(glm::vec3(x, y, z));

				scene->Add(dbc);
			}
			
			//scene->Add(Gray::CreateLight<Gray::PointLight>(Gray::CreateSource(dbcRoot)));
			scene->Add(Gray::CreateLight<Gray::PointLight>(Gray::CreateSource(Gray::Defaults::ORIGIN)));


			scene->GetCamera()->SetMoveEnabled(true);
			scene->GetCamera()->SetPos(glm::vec3(0.0f, 0.0f, 3.0f));

			GRAY_INFO("VertexArray " + std::to_string(sizeof(Gray::VertexArray)));
			GRAY_INFO("VertexBuffer " + std::to_string(sizeof(Gray::VertexBuffer)));
			GRAY_INFO("IndexBuffer " + std::to_string(sizeof(Gray::IndexBuffer)));
			GRAY_INFO("Shader " + std::to_string(sizeof(Gray::Shader)));
			renderLayer->SetScene(scene);
			return scene;
		}

	private:
		int n;
		float closeness;
	};
}