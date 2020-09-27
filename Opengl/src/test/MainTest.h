#pragma once

#include "Test.h"
#include "Util.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace test
{
	class MainTest: public Test
	{
	private:
		VertexBuffer* vb;
		IndexBuffer*  ib;
		VertexArray*  va;
		Shader*		  shader;
		Renderer*     renderer;
		Texture* tex;

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;

		glm::vec3 camPos;
		glm::vec3 objPos;

	public:
		MainTest();
		~MainTest();

		void onUpdate(float dt) override;
		void onRender() override;
		void onImGUIRender() override;
	};
}