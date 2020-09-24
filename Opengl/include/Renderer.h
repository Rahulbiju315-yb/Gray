#pragma once

#include <VertexArray.h>
#include <Shader.h>
#include <IndexBuffer.h>

class Renderer
{
public:
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void clear();
};
