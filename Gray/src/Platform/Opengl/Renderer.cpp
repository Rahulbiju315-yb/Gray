#include "grpch.h"

#include "Renderer.h"
#include "Gray/Events/Input.h"
#include "Gray/Events/KeyCodes.h"
#include "Gray/Application.h"
#include <GL/glew.h>

namespace Gray
{
	struct ScreenQuadData
	{
		NoCopy<VertexBuffer> vb;
		NoCopy<VertexArray> va;
	};
	const ScreenQuadData& ScreenQuad()
	{
		static ScreenQuadData sData;
		if (sData.vb->GetID() == 0)
		{
			float vertices[] =
			{
				-1.0f,  1.0f, 0.0f, 1.0f, // Top Left
				 1.0f, -1.0f, 1.0f, 0.0f, // Bottom Right
                -1.0f, -1.0f, 0.0f, 0.0f, // Bottom Left

				-1.0f,  1.0f, 0.0f, 1.0f, // Top Left
				 1.0f,  1.0f, 1.0f, 1.0f, // Top Right
				 1.0f, -1.0f, 1.0f, 0.0f, // Bottom Right
			};
			sData.vb->LoadBufferData(vertices, 24 * sizeof(float));

			BufferLayout bl;
			bl.Push<float>(2);
			bl.Push<float>(2);
			sData.va->SetAttribPointers(*sData.vb, bl);
		}

		return sData;
	}

	void Renderer::DrawScreenQuad(const Shader& shader) const
	{
		shader.Bind();
		const ScreenQuadData& sd = ScreenQuad();
		(sd.va)->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		shader.Bind();
		va.Bind();
		ib.Bind();

		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader
		, uint n_instances) const
	{
		shader.Bind();
		va.Bind();
		ib.Bind();

		glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0, n_instances);
	}

	void Renderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}