#pragma once

#include "Platform/Opengl/VertexBuffer.h"
#include "Platform/Opengl/VertexArray.h"
#include "Platform/Opengl/IndexBuffer.h"
#include "Platform/Opengl/Shader.h"
#include "Platform/Opengl/Renderer.h"

namespace Gray
{
	class Surface
	{
	public:
		Surface(int width = 10, int height = 10, float delta=0.1f);

		void GenerateFlatSurface(int width, int height, float delta);
		void GenerateUsingHMap(int width, int height, float delta, const std::string& path);
		void Render(const Shader& shader);
	private:
		NoCopy<VertexArray> va;
		NoCopy<IndexBuffer> ib;

		NoCopy<VertexBuffer> vb;
	};
}