#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Texture.h"

namespace Gray
{
	void DrawScreenQuad(const Shader& shader);
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, uint n_instances);

	void ClearDepth();
	void ClearColor(glm::vec4 color=glm::vec4(0));
	void ClearDepthColor(glm::vec4 color=glm::vec4(0));

}