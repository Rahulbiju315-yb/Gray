#include "grpch.h"
#include "Skybox.h"

namespace Gray
{
	Skybox::Skybox()
	{
		skyboxShader->LoadProgram("res/shaders/skyboxShader.shader");
	}

	void Skybox::LoadSkybox(const std::string path, const std::string ext)
	{
	}

	void Skybox::LoadSkybox(const std::vector<std::string> paths)
	{
	}

	void Skybox::RenderSkybox(const Camera& camera)
	{
		glDepthMask(GL_FALSE);
		skyboxShader->Bind();
		
	}
}