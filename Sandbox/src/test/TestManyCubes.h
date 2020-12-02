#pragma once

#include "Test.h"
#include "Gray/Graphics/Materials.h"
#include "Platform/Opengl/Texture.h"
#include "Gray/Graphics/Scene.h"
#include "Gray/Graphics/LightSource.h"
#include "Gray/Graphics/Source/SourceFactory.h"

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
			dbcRoot->SetRenderEnabled(false);

			Gray::Texture tex;
			tex.LoadTexture("res/textures/container2.png", GL_RGBA, GL_RGBA);

			Gray::Texture tex2;
			tex2.LoadTexture("res/textures/container2spec.png", GL_RGBA, GL_RGBA);

			Gray::Texture tex3;
			tex3.LoadTexture("res/textures/container2spec.png", GL_RGBA, GL_RGBA);

			for (int i = 0; i < n; i++)
			{
				std::unique_ptr<Gray::DebugCube> dbc = std::make_unique<Gray::DebugCube>(false, dbcRoot->GetShader());

				float x = (n * RAND_FLOAT - n/2) / closeness;
				float y = (n * RAND_FLOAT - n/2) / closeness;
				float z = (n * RAND_FLOAT - n/2) / closeness;

				dbc->GetMaterial()->SetDiffuse(tex);
				dbc->GetMaterial()->SetSpecular(tex2);
				//dbc->GetMaterial()->SetEmission(tex3);

				dbc->SetPos(glm::vec3(x, y, z));

				scene->Add(std::move(dbc));
			}
			
			scene->Add(std::make_shared<Gray::PointLight>(Gray::LightColor(),
				Gray::SourceFactory::CreateSource(scene->GetCamera())));

			scene->Add(std::make_shared<Gray::PointLight>(Gray::LightColor(),
				Gray::SourceFactory::CreateSource(Gray::Defaults::ORIGIN)));

			scene->GetCamera()->SetMoveEnabled(true);
			scene->GetCamera()->SetPos(glm::vec3(0.0f, 0.0f, 3.0f));

			renderLayer->SetScene(scene);
			return scene;
		}

	private:
		int n;
		float closeness;
	};
}