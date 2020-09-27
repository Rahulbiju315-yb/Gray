#pragma once

#include "Shader.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "BufferLayout.h"
#include "Renderer.h"

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
	static void sampleObject2(VertexBuffer*&, IndexBuffer*&, VertexArray*&, Shader*&);
	static void genCube(float x, float y, float z, float side, float* vertexPositions, int stride=3);
	static void genQuad(float x, float y, float z, float side, int dir, float* vertexPosition, int stride=3);
};