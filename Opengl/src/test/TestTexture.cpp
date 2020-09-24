#include "TestTexture.h"

#include <GL/glew.h>
#include "imgui.h"
#include "ImGuiFileDialog.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include<iostream>
#include <sstream>

namespace test
{
	TestTexture::TestTexture()
	{
		float vertices[20] =
		{
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // 0
			-0.5f, -0.5f, 0.0f,0.0f, 0.0f, // 1
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 2
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f  // 3
		};

		unsigned int indices[6] =
		{
			0, 1, 2,
			2, 3, 0
		};

		vb = new VertexBuffer(vertices, sizeof(vertices));
		ib = new IndexBuffer(indices, 6);

		BufferLayout layout;
		layout.push<float>(3);
		layout.push<float>(2);

		va = new VertexArray(*vb, layout);
		
		texture = new Texture("res/textures/wall.jpg", GL_RGB, GL_RGB);
		texture->bind(0);

		shader = new Shader("res/shaders/shader.shader");
		shader->bind();

		shader->setUniform("Tex1", 0);
		shader->setUniform("model", glm::mat4(1.0f));
		shader->setUniform("view", glm::mat4(1.0f));
		shader->setUniform("projection", glm::mat4(1.0f));

		shader->unbind();

		renderer = new Renderer();
	}

	TestTexture::~TestTexture()
	{
		delete vb;
		delete va;
		delete ib;
		delete shader;
		delete texture;
		delete renderer;
	}

	void test::TestTexture::onRender()
	{
		renderer->clear();
		renderer->draw(*va, *ib, *shader);
	}

	void test::TestTexture::onUpdate(float dt)
	{

	}

	void test::TestTexture::onImGUIRender()
	{
		// open Dialog Simple
		if (ImGui::Button("Open File Dialog"))
			igfd::ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", "{.jpg,.png,.jpeg}", ".");

		// display
		if (igfd::ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey"))
		{
			// action if OK
			if (igfd::ImGuiFileDialog::Instance()->IsOk == true)
			{
				std::string filePathName = igfd::ImGuiFileDialog::Instance()->GetFilePathName();
				std::string filePath = igfd::ImGuiFileDialog::Instance()->GetCurrentPath();
				// action
				
				int indexOfPeriod = filePathName.rfind(".");
				std::string extension = filePathName.substr(indexOfPeriod, 
					filePathName.size() - indexOfPeriod + 1);

				if (extension == ".png")
				{
					texture = new Texture(filePathName, GL_RGBA, GL_RGBA);
		
				}
				else
				{
					texture = new Texture(filePathName, GL_RGB, GL_RGB);
				}

				texture->bind(0);
			}
			// close
			igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");

		}
		
	}

}