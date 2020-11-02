#pragma once

#include "Platform/Opengl/Shader.h"
#include "Platform/Opengl/Texture.h"
#include "Platform/Opengl/VertexBuffer.h"
#include "Platform/Opengl/VertexArray.h"
#include "Platform/Opengl/IndexBuffer.h"
#include "Platform/Opengl/Texture.h"
#include "Platform/Opengl/BufferLayout.h"
#include "Platform/Opengl/Renderer.h"

//for debugging purposes only
namespace Gray
{
	const int X = 0;
	const int Y = 1;
	const int Z = 2;

	struct Vertex
	{
		float position[3];
		float texCoord[2];
	};

	class Util
	{
	public:
		static void sampleObject1(VertexBuffer*&, IndexBuffer*&, VertexArray*&, Shader*&);
		static void sampleObject2(VertexBuffer*&, IndexBuffer*&, VertexArray*&, Shader*&, bool loadSampleShader=true);
		static void genCube(float x, float y, float z, float side, float* vertexPositions, int stride = 3);
		static void genQuad(float x, float y, float z, float side, int dir, float* vertexPosition, int stride = 3);
		static void genTri(std::vector<glm::vec3> p, float* vertexPositions, int stride);
	};
}