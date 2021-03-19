#include "grpch.h"
#include "MeshEditor.h"
#include "ImGuizmo/ImGuizmo.h"
#include "imgui.h"

#include "Gray/Mesh/MeshData.h"
#include "Gray/Mesh/Mesh.h"
#include "Gray/Resources/GlobalRM.h"
#include "Gray/Resources/TextureManager.h"

#include "Gray/Math/Constants.h"
#include "Editor.h"
#include "Platform/Opengl/Renderer.h"
#include "GLFW/glfw3.h"

namespace Gray
{
	MeshEditor::MeshEditor()
		: selectedIndex(-1)
	{
		meshData.push_back(GetUnitCube2MeshData());
		meshData.push_back(GetSphereMeshData(1.0f, 18, 36));
	}

	void MeshEditor::DrawUI(const Editor& editor)
	{
		UIAddButtons();
		UISelectionPanel();

		if (selectedIndex >= 0)
		{
			RenderableMesh& rmesh = rmeshes[selectedIndex];
			if (editor.GizmoRender(rmesh.modelMatrix))
				rmesh.invModelMatrix = glm::inverse(rmesh.modelMatrix);
		}
	}

	const std::vector<RenderableMesh>& MeshEditor::GetRMeshes() const
	{
		return rmeshes;
	}

	void MeshEditor::OnEvent(Event& e)
	{
		EventType type = e.GetType();
		if (type == EventType::KeyPressed)
			OnKeyPressed(static_cast<KeyPressedEvent&>(e));
	}

	void MeshEditor::UIAddButtons()
	{
		if (ImGui::Button("Add cube"))
		{
			static int cc = 0;
			rmeshes.push_back(RenderableMesh{ CreateMeshPNT(meshData[0]), UNIT_MAT4, UNIT_MAT4 });
			names.push_back("cube" + std::to_string(++cc));
			meshDataID.push_back(0);
		}

		if (ImGui::Button("Add sphere"))
		{
			static int sc = 0;
			rmeshes.push_back(RenderableMesh{ CreateMeshPNT(meshData[1]), UNIT_MAT4, UNIT_MAT4 });
			names.push_back("Sphere" + std::to_string(++sc));
			meshDataID.push_back(1);
		}
	}

	void MeshEditor::UISelectionPanel()
	{
		static bool changed = false;

		if (!names.empty())
		{

			std::vector<const char*> cnames;
			cnames.reserve(names.size());

			for (const std::string& name : names)
			{
				cnames.push_back(name.c_str());
			}

			changed = ImGui::ListBox("Items : \n", &selectedIndex, &(cnames[0]), static_cast<int>(names.size()));
		}
	}

	void MeshEditor::OnKeyPressed(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == GLFW_KEY_D)
		{
			if (selectedIndex >= 0)
			{
				static uint i = 1;
				assert(selectedIndex < meshDataID.size());
				uint meshID = meshDataID[selectedIndex];
				
				assert(meshID < meshData.size());
				const MeshData& meshD = meshData[meshID];
				const RenderableMesh& srmesh = rmeshes[selectedIndex];
				
				rmeshes.push_back(RenderableMesh { CreateMeshPNT(meshD), srmesh.modelMatrix, srmesh.invModelMatrix });
				names.push_back(names[selectedIndex] + "_" + std::to_string(i++));
				meshDataID.push_back(meshID);
			}
		}
	}
}