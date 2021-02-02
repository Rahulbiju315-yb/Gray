#pragma once

#include "Platform/Opengl/Cubemap.h"
#include "Platform/Opengl/Shader.h"
#include "Platform/Opengl/VertexArray.h"
#include "Platform/Opengl/VertexBuffer.h"
#include "Platform/Opengl/IndexBuffer.h"

namespace Gray
{
	class Skybox
	{
	public:
		Skybox();
		void LoadSkybox(const std::string path, const std::string ext);
		void LoadSkybox(const std::vector<std::string> paths);

		void RenderSkybox(const glm::mat4& view , const Shader& shader);

	private:
		NoCopy<Cubemap> cubeMap;

		NoCopy<VertexBuffer> vb;
		NoCopy<IndexBuffer> ib;
		NoCopy<VertexArray> va;
	};
}