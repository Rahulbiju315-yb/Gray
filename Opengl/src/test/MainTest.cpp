#include "MainTest.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

#include "imgui.h"

const glm::mat4 UNIT_MAT4 = glm::mat4(1.0f);

glm::mat4 rotation = glm::mat4(1.0f);
glm::mat4 translationA = glm::mat4(1.0f);
glm::mat4 translationO = glm::mat4(1.0f);

glm::vec3 X_AXIS = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 Y_AXIS = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 Z_AXIS = glm::vec3(0.0f, 0.0f, 1.0f);

test::MainTest::MainTest()
{
	vb = nullptr;
	ib = nullptr;
	debug = nullptr;
	va = nullptr;
	shader = nullptr;
	renderer = new Renderer();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
	tex = new Texture("res/textures/t4.jpg", GL_RGB, GL_RGB);
	tex->bind();

	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1000.0f / 1000.0f, 0.1f, 100.0f);

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.5f));

	Util::sampleObject2(vb, ib, debug, va, shader);
	
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
	//renderer->draw(*va, *debug, *shader);
}

void test::MainTest::onImGUIRender()
{
	bool changedR = ImGui::SliderFloat3("Rotation Object", &objRotation.x, 0.0f, 360.0f, "%.3f", 1.0f);
	if (changedR)
	{
		rotation = glm::rotate(UNIT_MAT4, glm::radians(objRotation.x), X_AXIS);
		rotation = glm::rotate(rotation, glm::radians(objRotation.y), Y_AXIS);
	    rotation = glm::rotate(rotation, glm::radians(objRotation.z), Z_AXIS);
	}

	bool changedCM = ImGui::SliderFloat3("Camera Pos", &camPos.x, -2.0f, 2.0f, "%.3f", 1.0f);
	if (changedCM)
	{
		view = glm::translate(UNIT_MAT4, -camPos);
		shader->setUniform("view", view);
	}
	
	bool changedTO = ImGui::SliderFloat3("Object Pos", &objPos.x, -2.0f, 2.0f, "%.3f", 1.0f);
	if (changedTO)
	{
		translationO = glm::translate(UNIT_MAT4, objPos);
	}

	bool changedTA = ImGui::SliderFloat3("Axis Pos", &axisPos.x, -2.0f, 2.0f, "%.3f", 1.0f);
	if (changedTA)
	{
		translationA = glm::translate(UNIT_MAT4, axisPos);
		translationO = glm::translate(UNIT_MAT4, -axisPos);
	}

	if (changedTO || changedR)
	{
		model =  translationO * rotation * translationA;
		shader->setUniform("model", model);
	}
}

