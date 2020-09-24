#pragma once
#include "Test.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "BufferLayout.h"
#include "Renderer.h"

namespace test
{
	class TestTexture : public Test 
	{
	private:
		Shader *shader;
		VertexBuffer *vb;
		VertexArray *va;
		IndexBuffer *ib;
		Texture *texture;
		Renderer* renderer;

	public:
		TestTexture();
		~TestTexture();

		void onRender() override;
		void onUpdate(float dt) override;
		void onImGUIRender() override;

	};
}