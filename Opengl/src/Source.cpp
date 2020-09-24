#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "BufferLayout.h"
#include "Texture.h"
#include "Renderer.h"

#include "test/TestMenu.h"
#include "test/TestClearColor.h"
#include "test/TestTexture.h"
#include "test/TestViewPort.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"



int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glewInit();


	// Setup Platform/Renderer bindings
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

	// Init
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//EndInit


	Texture t1((const std::string&)"res/textures/wall.jpg", GL_RGB, GL_RGB);
	Texture t2((const std::string&)"res/textures/awesomeface.png", GL_RGBA, GL_RGBA);
	

	float vertices[] =
	{
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f, 0.5f, 1.0f
	};

	unsigned int indices[] =
	{
		0, 1, 2
	};

	VertexBuffer vb(vertices, sizeof(vertices));
	IndexBuffer ib(indices, 3);

	BufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);

	VertexArray va(vb, layout);

	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

	std::string fp = "res\\shaders\\shader.shader";
	Shader shader(fp);

	t1.bind(1);
	Renderer renderer;

	
	shader.bind();
	shader.setUniform("Tex1", 1);
	shader.setUniform("model", model);
	shader.setUniform("view", view);
	shader.setUniform("projection", projection);
	
	test::TestMenu *testMenu = new test::TestMenu();
	testMenu->addTest<test::TestClearColor>("Clear Color");
	testMenu->addTest<test::TestViewPort>("View Port");
	testMenu->addTest<test::TestTexture>("Texture");

	int count = 0;
	bool mainWindow = true;


	while (!glfwWindowShouldClose(window))
	{
		if (!testMenu->isTestSelected())
		{
			renderer.clear();
			renderer.draw(va, ib, shader);
		}
		testMenu->onUpdate(0.0f);
		testMenu->onRender();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			testMenu->onImGUIRender();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}