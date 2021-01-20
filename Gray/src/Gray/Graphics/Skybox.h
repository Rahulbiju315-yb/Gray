#pragma once

#include "Platform/Opengl/Cubemap.h"
#include "Platform/Opengl/Shader.h"
#include "Camera.h"

namespace Gray
{
	class Skybox
	{
	public:
		Skybox();
		void LoadSkybox(const std::string path, const std::string ext);
		void LoadSkybox(const std::vector<std::string> paths);

		void RenderSkybox(const Camera& camera);

	private:

		NoCopy<Shader>  skyboxShader;
		NoCopy<Cubemap> cubeMap;
	};
}