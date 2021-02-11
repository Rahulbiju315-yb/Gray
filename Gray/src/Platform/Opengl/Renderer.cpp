#include "grpch.h"

#include "Renderer.h"
#include "Gray/Events/Input.h"
#include "Gray/Events/KeyCodes.h"
#include "Gray/Application.h"
#include <GL/glew.h>
#include "Gray/Mesh/Mesh.h"

namespace Gray
{
	struct ScreenQuadData
	{
		NoCopy<VertexBuffer> vb;
		NoCopy<VertexArray> va;
	};

	const NoCopyMesh& ScreenQuad()
	{
		static NoCopyMesh mesh;
		static bool init = false;

		if (!init)
		{
			init = true;
			float vertices[] =
			{
				-1.0f,  1.0f, 0.0f, 1.0f, // Top Left
				 1.0f, -1.0f, 1.0f, 0.0f, // Bottom Right
                -1.0f, -1.0f, 0.0f, 0.0f, // Bottom Left

				-1.0f,  1.0f, 0.0f, 1.0f, // Top Left
				 1.0f,  1.0f, 1.0f, 1.0f, // Top Right
				 1.0f, -1.0f, 1.0f, 0.0f, // Bottom Right
			};
			mesh.vb->LoadBufferData(vertices, 24 * sizeof(float));

			BufferLayout bl;
			bl.Push<float>(2);
			bl.Push<float>(2);
			mesh.va->SetAttribPointers(*mesh.vb, bl);
		}

		return mesh;
	}

	void DrawScreenQuad(const Shader& shader)
	{
		shader.Bind();
		const NoCopyMesh& sd = ScreenQuad();
		(sd.va)->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
	{
		assert(va.GetID() != 0);
		assert(ib.GetID() != 0);
		shader.Bind();
		va.Bind();
		ib.Bind();

		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader
		, uint n_instances)
	{
		shader.Bind();
		va.Bind();
		ib.Bind();

		glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0, n_instances);
	}

	void ClearColor(glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void ClearDepth()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void ClearDepthColor(glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}