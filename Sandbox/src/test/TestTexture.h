#pragma once

#pragma once

#include "Test.h"
#include "Gray/Graphics/Materials.h"
#include "Platform/Opengl/Texture.h"


#include "Gray/Graphics/Light/PointLight.h"
#include "Gray/Resources/TextureManager.h"

#include "Gray/Graphics/Model/RenderableModel.h"
#include "Platform/Opengl/FrameBuffer.h"
#include "Platform/Opengl/Renderer.h"

#include <glm/gtc/type_ptr.hpp>
#include "Gray/Math/Constants.h"

#define RAND_FLOAT (float)rand() / RAND_MAX

namespace Test
{
	void fill(float* arr, float f, int n);

	class TestTexture : public Test
	{
	public:
		TestTexture()
		{
		}

		void OnInit() override
		{
			texture = tm.GetTexture("res/textures/matrix.jpg");
			texture->Bind(1);

			shader->LoadProgram("res/shaders/textureShader.shader");
			shader->SetUniform("tex", 1);

		}

		void OnLoad(Gray::RenderableModel& model, int rindex)
		{
			
		}

		void Render(float dt) override
		{
			if(tm.RequireInit())
				tm.InitTextures();

			Gray::DrawScreenQuad(*shader);
		}

	private:
		
		Gray::TextureManager tm;
		Gray::NoCopy<Gray::Shader> shader;

		Gray::WeakRef<Gray::Texture> texture;
	};

}
