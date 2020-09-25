#include "MainTest.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

#include "imgui.h"

const glm::mat4 UNIT_MAT4 = glm::mat4(1.0f);

test::MainTest::MainTest()
{
	vb = nullptr;
	ib = nullptr;
	va = nullptr;
	shader = nullptr;
	renderer = new Renderer();
	tex = new Texture("res/textures/wall.jpg", GL_RGB, GL_RGB);
	tex->bind();

	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1280.0f / 1000.0f, 0.1f, 100.0f);

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.5f));

	Util::sampleObject1(vb, ib, va, shader);
	
	shader->bind();
	shader->setUniform("model", model);
	shader->setUniform("view", view);
	shader->setUniform("projection", projection);
	shader->unbind();

	camPos = glm::vec3(0.0f, 0.0f, 0.5f);

}

test::MainTest::~MainTest()
{
	delete vb;
	delete ib;
	delete va;
	delete shader;
	delete renderer;
	delete tex;
}

void test::MainTest::onUpdate(float dt)
{
	
}

void test::MainTest::onRender()
{
	renderer->draw(*va, *ib, *shader);
}

void test::MainTest::onImGUIRender()
{
	bool changed = ImGui::SliderFloat3("Camera Pos", &camPos.x, -2.0f, 2.0f, "%.3f", 1.0f);
	if (changed)
	{
		view = glm::translate(UNIT_MAT4, -camPos);
		shader->setUniform("view", view);
	}
}

