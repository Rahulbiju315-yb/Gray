#include "TestTexture.h"

#include <GL/glew.h>
#include "imgui.h"
#include "ImGuiFileDialog.h"

#include<iostream>
#include <sstream>

namespace test
{
	test::TestTexture::TestTexture(const Shader& sh)
		:shader(sh)
	{

	}

	test::TestTexture::~TestTexture()
	{

	}

	void test::TestTexture::onRender()
	{

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

				Texture *tex;
				
				int indexOfPeriod = filePathName.rfind(".");
				std::string extension = filePathName.substr(indexOfPeriod, 
					filePathName.size() - indexOfPeriod + 1);

				if (extension == ".png")
				{
					tex = new Texture(filePathName, GL_RGBA, GL_RGBA);
		
				}
				else
				{
					tex = new Texture(filePathName, GL_RGB, GL_RGB);
				}

				tex->bind(1);
				delete(tex);
			}
			// close
			igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");

		}
		
	}

}