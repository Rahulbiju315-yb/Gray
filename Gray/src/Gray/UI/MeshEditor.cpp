#include "grpch.h"
#include "MeshEditor.h"
#include "ImGuizmo/ImGuizmo.h"
#include "imgui.h"

#include "Gray/Mesh/MeshData.h"
#include "Gray/Mesh/Mesh.h"
#include "Gray/Resources/GlobalRM.h"
#include "Gray/Resources/TextureManager.h"

#include "Gray/Math/Constants.h"
#include "Gizmo.h"
#include "Platform/Opengl/Renderer.h"
#include "GLFW/glfw3.h"

#include "Gray/Algo/Search.h"
namespace Gray
{
	MeshEditor::MeshEditor()
		: selectedMeshIndex(-1),
		  selectedMatIndex(-1)
	{
		meshData.push_back(GetUnitCube2MeshData());
		meshData.push_back(GetSphereMeshData(1.0f, 18, 36));
	}


	void MeshEditor::DrawUI(const EditorCamera& camera, SceneInfo& scene)
	{
		UIAddButtons();
		UIMeshSelectionPanel();

		if (selectedMeshIndex >= 0)
		{
			assert(selectedMeshIndex < scene.rmeshEntities.GetSize());
			RenderableMesh& rmesh = scene.rmeshEntities.GetField<RenderableMesh>()[selectedMeshIndex];
			if (Gizmo::GizmoRender(rmesh.modelMatrix, camera.GetView(), camera.GetProjection()))
				rmesh.invModelMatrix = glm::inverse(rmesh.modelMatrix);
		}
	}

	void MeshEditor::UIAddButtons()
	{
		if (ImGui::Button("Add cube"))
		{
			static int cc = 0;

			Material mat;
			mat.SetDiffuse(txm.GetTexture("res/textures/wood.png"));
			mat.SetSpecular(txm.GetTexture("res/textures/wood.png"));

			RenderableMesh rmesh{ CreateMeshPNT(meshData[0]), UNIT_MAT4, UNIT_MAT4, NullValues::nullMaterial };
			std::string name{ "cube" + std::to_string(++cc) };
			EntityIndex<MeshData> meshInd {0};


			selectedMeshIndex = names.size() - 1;
		}

		if (ImGui::Button("Add sphere"))
		{
			static int sc = 0;

			Material mat;
			mat.SetDiffuse(txm.GetTexture("res/textures/wood.png"));
			mat.SetSpecular(txm.GetTexture("res/textures/wood.png"));

			(*rmeshes_ptr).push_back(RenderableMesh{ CreateMeshPNT(meshData[1]), UNIT_MAT4, UNIT_MAT4, Default<Material>()});
			names.push_back("Sphere" + std::to_string(++sc));
			cnames.push_back(names.back().c_str());
			meshDataID.push_back(1);

			selectedMeshIndex = names.size() - 1;
		}
	}

	bool Equals(const Material& m1, const Material& m2)
	{
		return m1.GetID() == m2.GetID();
	}

	void MeshEditor::UIMeshSelectionPanel()
	{
		static bool changed = false;
		if (!names.empty())
		{
			changed = ImGui::ListBox("Items : \n", &selectedMeshIndex, &(cnames[0]), static_cast<int>(names.size()));
			if (changed)
			{
				assert(selectedMeshIndex < (*rmeshes_ptr).size());
				const RenderableMesh& rmesh = (*rmeshes_ptr)[selectedMeshIndex];
				const std::vector<Material>& materials = (*matList_ptr).GetMaterials();

				int index = Lsearch(materials, rmesh.material, Equals);
				if (index != -1)
				{
					selectedMatIndex = index;
				}
			}
		}
	}

	void MeshEditor::UIMaterialSelectionPanel()
	{
		const std::vector<const char*> cnames = (*matList_ptr).GetCNames();
		if (!(cnames.empty()))
		{
			bool changed = ImGui::Combo("Mesh Materials :", &selectedMatIndex, &(cnames[0]), static_cast<int>(cnames.size()));
			if(changed)
			{
				assert(selectedMeshIndex < (*rmeshes_ptr).size());
				RenderableMesh& rmesh = (*rmeshes_ptr)[selectedMeshIndex];
				const Material& sMat = (*matList_ptr).GetMaterials()[selectedMatIndex];
				rmesh.material = sMat;
			}
		}
	}

	void MeshEditor::OnKeyPressed(const KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == GLFW_KEY_D && e.GetMods() == 0)
		{
			if (selectedMeshIndex >= 0)
			{
				static uint i = 1;
				assert(selectedMeshIndex < meshDataID.size());
				uint meshID = meshDataID[selectedMeshIndex];
				
				assert(meshID < meshData.size());
				const MeshData& meshD = meshData[meshID];
				const RenderableMesh& srmesh = (*rmeshes_ptr)[selectedMeshIndex];
				
				(*rmeshes_ptr).push_back(RenderableMesh { CreateMeshPNT(meshD), srmesh.modelMatrix, srmesh.invModelMatrix });
				names.push_back(names[selectedMeshIndex] + "_" + std::to_string(i++));
				meshDataID.push_back(meshID);
			}
		}
	}

}