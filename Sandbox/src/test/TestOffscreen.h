#pragma once

#include "Test.h"
#include "Gray/Graphics/Materials.h"
#include "Platform/Opengl/Texture.h"

#include "Gray/Graphics/Scene.h"

#include "Gray/Graphics/Light/PointLight.h"
#include "Gray/Graphics/Source/SourceFactory.h"
#include "Gray/Graphics/Resource/ResourceManager.h"

#include "Gray/Graphics/Model/RenderableModel.h"
#include "Platform/Opengl/FrameBuffer.h"
#include "Platform/Opengl/Renderer.h"

#include <glm/gtc/type_ptr.hpp>

#define RAND_FLOAT (float)rand() / RAND_MAX

namespace Test
{
	void fill(float* arr, float f, int n);

	class TestOffscreen : public Test
	{
	public:
		TestOffscreen()
			: scene(Gray::Scene(1))
		{

			// FrameBuffer setup
			colorAttachment->LoadEmptyTexture(1200, 700, GL_RGB, GL_RGB);
			depthAttachment->LoadDepthTexture(1200, 700);
			debug = Gray::GetTexture("res/textures/matrix.jpg");

			offScreen->AddAttachment(*colorAttachment, Gray::AttachmentType::Color);
			offScreen->AddAttachment(*depthAttachment, Gray::AttachmentType::Depth);

			colorAttachment->Bind(0);

			GRAY_INFO("Is offscreen complete ? " + std::to_string(offScreen->IsComplete()));
			
			// Shader loading and uniform setting
			textureShader->LoadProgram("res/shaders/textureShader.shader");
			textureShader->SetUniform("tex", 1);

			fill(kernel, 1.0 / 9, 9);

		}

		Gray::Scene* OnInit() override
		{

			int index = scene.CreateRModel();
			scene.SetModelPath(index, GUN);

			auto source = std::make_unique<Gray::CameraSource>(&scene.GetCamera());
			index = scene.CreateLight(Gray::LightType::PointLight, std::move(source));
			scene.GetLight(index, Gray::LightType::PointLight).SetAttenuation(1.0f, 0, 0);

			scene.InitForRender();
			scene.ReloadRModels(*this);
			return &scene;
		}

		void OnLoad(Gray::RenderableModel& model, int rindex)
		{
			Gray::RenderableModel& rmodel = scene.GetRModel(rindex);
			std::vector<float> offsets;
			offsets.reserve(3);
			offsets.push_back(0);
			offsets.push_back(0);
			offsets.push_back(0);
			rmodel.SetInstanceOffsets(std::move(offsets));
		}

		void OnUpdate(float dt) override
		{
			if (scene.IsSceneComplete())
			{
				offScreen->Bind();
				Gray::ClearDepthColor(glm::vec4(0.1f, 0.19f, 0.25f, 1.0f));
				glEnable(GL_DEPTH_TEST);

				scene.RenderModels();

				offScreen->Unbind();

				Gray::ClearColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
				colorAttachment->Bind(1);
				DrawScreenQuad(*textureShader);
			}
			else
			{
				scene.LoadResources(*this);
			}
		}

		void OnImguiRender(float dt) override
		{
			KernelDebug();
		}


		// Debug Methods

		void KernelDebug()
		{
			static float av = 1.0f / 9;
			static bool changed = true;
			static float kernelArr[9] = 
			{ 
				av, av, av,
			    av, av, av,
				av, av, av
			};

			ImGui::LabelText("Kernel", "");

			changed = ImGui::InputFloat3("Row 1", &kernel[0], 0, 1);
			changed |= ImGui::InputFloat3("Row 2", &kernel[3], 0, 1);
			changed |= ImGui::InputFloat3("Row 3", &kernel[6], 0, 1);

			if (changed)
			{
				float sum = 0;
				for (int i = 0; i < 9; i++)
					sum += kernelArr[i];

				for(int i = 0; i < 9; i++)
					textureShader->SetUniform("kernel["+std::to_string(i)+"]", kernel[i] / sum);
			}

		}

	private:
		float kernel[9];

		Gray::Scene scene;
		Gray::NoCopy<Gray::FrameBuffer> offScreen;
		Gray::NoCopy<Gray::Texture> colorAttachment;
		Gray::NoCopy<Gray::Texture> depthAttachment;
		Gray::WeakRef<Gray::Texture> debug;

		Gray::NoCopy<Gray::Shader> textureShader;

	};

	// fills an array with f for first n elements
	void fill(float* arr, float f, int n)
	{
		for (int i = 0; i < n; i++)
			arr[i] = f;
	}
}
