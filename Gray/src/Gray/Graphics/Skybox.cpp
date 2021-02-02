#include "grpch.h"
#include "Skybox.h"
#include "Gray/Mesh/MeshData.h"
#include "Platform/Opengl/Renderer.h"

namespace Gray
{
	Skybox::Skybox()
	{
		MeshData meshD = GetUnitCube1MeshData();

		vb->LoadBufferData(&(meshD.vertices[0]), SizeOfVertices(meshD));
		ib->LoadBufferData(&(meshD.faces[0].v0), CountOfIndices(meshD));

		BufferLayout bl;
		bl.Push<float>(3);
		bl.Push<float>(3);
		bl.Push<float>(2);

		va->SetAttribPointers(*vb, bl);
	}

	void Skybox::LoadSkybox(const std::string path, const std::string ext)
	{
		cubeMap->LoadCubeMap(path, ext, 10);
	}

	void Skybox::LoadSkybox(const std::vector<std::string> paths)
	{
		assert(false);
	}

	void Skybox::RenderSkybox(const glm::mat4& view, const Shader& shader)
	{
		glDepthMask(GL_FALSE);
		cubeMap->Bind(10);
		shader.Bind();
		shader.SetUniform("view", glm::mat4(glm::mat3(view)));
		Draw(*va, *ib, shader);
		glDepthMask(GL_TRUE);

	}
}