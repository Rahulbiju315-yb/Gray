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

		std::shared_ptr<Gray::Scene> OnInit() override
		{
			scene = std::make_shared<Gray::Scene>(2); // Create 2 renderables

			auto model1 = scene->CreateRenderModel();
			model1->LoadModel("res/models/47-obj/Handgun_obj.obj", false);

			auto model2 = scene->CreateRenderModel();
			model2->LoadModel("res/models/backpack/backpack.obj", true);
			model2->GetTransform().SetPos(glm::vec3(5, 0, 5));

			auto source = std::make_unique<Gray::CameraSource>(scene->GetCamera());
			auto ls = scene->CreateLight(Gray::LightType::PointLight, std::move(source));
			ls->SetAttenuation(1.0f, 0.07f, 0.14f);

			return scene;
		}

		void OnUpdate(float dt) override
		{
			for (auto& renderable : *scene)
			{
				renderable.OnUpdate(dt);
			}
		}

	private:
		std::shared_ptr<Gray::Scene> scene;
	};
}