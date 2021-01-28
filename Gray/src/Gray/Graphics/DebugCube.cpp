#include "grpch.h"
#include "DebugCube.h"
#include "Gray/Mesh/MeshData.h"
#include "Gray/Mesh/Mesh.h"
#include "Gray/Graphics/Defaults.h"
#include "Platform/Opengl/Renderer.h"
//#include "ImGuizmo/ImGuizmo.h"

namespace Gray
{
	DebugCube::DebugCube()
	{
		MeshData meshD = GetUnitCube1MeshData();
		mesh = CreateMeshPNT(meshD);

		model = glm::mat4(1);
	}

	void DebugCube::Render(const Shader& shader)
	{
		shader.SetUniform("model", model);
		Draw(*mesh.va, *mesh.ib, shader);
	}
}