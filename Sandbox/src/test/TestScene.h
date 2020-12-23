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
	class TestScene : public Test
	{
	public:
		TestScene()
		{
			
		}

		std::shared_ptr<Gray::Scene> OnInit(Gray::RenderLayer* renderLayer) override
		{
			std::shared_ptr<Gray::Scene> scene = std::make_shared<Gray::Scene>();
			std::shared_ptr<Gray::DebugCube> dbcRoot = std::make_shared<Gray::DebugCube>();
			dbcRoot->SetRenderEnabled(true);

			Gray::Texture tex1;
			tex1.LoadTexture("res/textures/container2.png", GL_RGBA, GL_RGBA);

			Gray::Texture tex2;
			tex2.LoadTexture("res/textures/container2spec.png", GL_RGBA, GL_RGBA);

			Gray::Texture tex3;
			tex3.LoadTexture("res/textures/container2spec.png", GL_RGBA, GL_RGBA);

			Gray::Material* material = dbcRoot->GetMaterial();
			material->SetDiffuse(tex1);
			material->SetSpecular(tex2);

			
			
			//scene->Add(Gray::CreateLight<Gray::PointLight>(Gray::CreateSource(dbcRoot)));
			Gray::SharedLightSource ls =
				Gray::CreateLight<Gray::PointLight>(Gray::CreateSource(Gray::Defaults::ORIGIN));
			scene->Add(ls);


			scene->GetCamera()->SetMoveEnabled(true);
			scene->GetCamera()->SetPos(glm::vec3(0.0f, 0.0f, 3.0f));
			renderLayer->SetScene(scene);

			return scene;
		}

	private:
	};
}