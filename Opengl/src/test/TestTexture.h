#pragma once
#include "Test.h"
#include "Shader.h"
#include "Texture.h"

namespace test
{
	class TestTexture : public Test 
	{
	private:
		const Shader& shader;

	public:
		TestTexture(const Shader&);
		~TestTexture();

		void onRender() override;
		void onUpdate(float dt) override;
		void onImGUIRender() override;

	};
}