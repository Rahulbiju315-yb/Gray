#pragma once
#include "Test.h"
#include "Platform/Opengl/Shader.h"
#include "Platform/Opengl/Texture.h"
#include "Platform/Opengl/VertexBuffer.h"
#include "Platform/Opengl/VertexArray.h"
#include "Platform/Opengl/IndexBuffer.h"
#include "Platform/Opengl/Texture.h"
#include "Platform/Opengl/BufferLayout.h"
#include "Platform/Opengl/Renderer.h"

namespace Gray
{
	namespace test
	{
		class TestTexture : public Test
		{
		private:
			Shader* shader;
			VertexBuffer* vb;
			VertexArray* va;
			IndexBuffer* ib;
			Texture* texture;
			Renderer* renderer;

		public:
			TestTexture();
			~TestTexture();

			void onRender() override;
			void onUpdate(float dt) override;
			void onImGUIRender() override;

		};
	}
}