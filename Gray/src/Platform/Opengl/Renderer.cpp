#include "grpch.h"

#include "Renderer.h"
#include <GL/glew.h>

namespace Gray
{
	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
	{
		shader.Bind();
		va.Bind();
		ib.Bind();

		//GRAY_CORE_INFO(std::to_string(ib.GetCount()));
		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}