#pragma once

#include "Test.h"
#include "Gray/Graphics/Materials.h"
#include "Platform/Opengl/Texture.h"

namespace Test
{
	#define RAND_FLOAT (float)rand() / RAND_MAX
	class TestManyCubes : public Test
	{
	public:
		TestManyCubes(int n, float closeness=20.f) : n(n), closeness(closeness)
		{
			
		}

		void OnInit(Gray::RenderLayer* renderLayer) override
		{
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

				renderLayer->AddRenderable(std::move(dbc));
				
			}
			
			GRAY_INFO("Size :" + std::to_string(sizeof(std::tuple<float, float, float>)));
			renderLayer->SetCameraMovementEnabled(true);
			renderLayer->SetCameraPos(glm::vec3(0.0f, 0.0f, 3.0f));
		}

	private:
		int n;
		float closeness;
	};
}