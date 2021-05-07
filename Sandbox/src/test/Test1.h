#pragma once
#include "Test.h"
#include "Gray.h"
namespace Test
{
	class Test1
	{
	public :
		virtual void OnInit()
		{
			colorAttachment->LoadEmptyTexture(1200, 700, GL_RGB, GL_RGB);
			depthAttachment->LoadDepthTexture(1200, 700);

			fb->AddAttachment(*colorAttachment, Gray::AttachmentType::Color);
			fb->AddAttachment(*depthAttachment, Gray::AttachmentType::Depth);

			textureShader->LoadProgram("res/shaders/textureShader.shader");
			textureShader->SetUniform("tex", 1);

			
		}

		virtual void PreRender(float dt)
		{
		}

		virtual void Render(float dt)
		{
		}

		virtual void PostRender(float dt)
		{
		}

		virtual void OnEvent(Gray::Event& e) 
		{
		}

	private:
		FrameBuffer fb;
		Texture colorAttachment;
		Texture depthAttachment;
		Shader textureShader;

		Gray::ModelManager mm;
	};
}