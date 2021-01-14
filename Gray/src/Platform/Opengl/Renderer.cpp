#include "grpch.h"

#include "Renderer.h"
#include "Gray/Events/Input.h"
#include "Gray/Events/KeyCodes.h"
#include "Gray/Application.h"
#include <GL/glew.h>

namespace Gray
{
	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		shader.Bind();
		va.Bind();
		ib.Bind();

		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}