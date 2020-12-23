#pragma once

#pragma once
#pragma once

#include "Test.h"
#include "Gray/Graphics/Materials.h"
#include "Platform/Opengl/Texture.h"

#include "Gray/Graphics/Scene.h"

#include "Gray/Graphics/Light/PointLight.h"
#include "Gray/Graphics/Source/SourceFactory.h"

#include "Gray/Graphics/Model/RenderableModel.h"
#include "Platform/Opengl/Opengl.h"

namespace Test
{
	#define RAND_FLOAT (float)rand() / RAND_MAX
	class TestModelLoading : public Test
	{
	public:
		TestModelLoading()
		{
			
		}

		std::shared_ptr<Gray::Scene> OnInit(Gray::RenderLayer* renderLayer) override
		{
			std::shared_ptr<Gray::Scene> scene = std::make_shared<Gray::Scene>();
			
			std::unique_ptr<Gray::Model> temp = std::make_unique<Gray::Model>();
			temp->LoadModel("res/models/backpack", "backpack.obj");

			std::unique_ptr<Gray::RenderableModel> model = std::make_unique<Gray::RenderableModel>(std::move(temp));
			model->GetTransform().SetPos(glm::vec3(0));
			scene->Add(Gray::CreateLight<Gray::PointLight>(Gray::CreateSource(scene->GetCamera())));
			scene->Add(std::move(model));

			renderLayer->SetScene(scene);
			return scene;
		}

	};
}