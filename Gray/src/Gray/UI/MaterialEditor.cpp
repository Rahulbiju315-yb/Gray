#include "grpch.h"
#include "MaterialEditor.h"
#include "Editor.h"
#include "Gray/Events/Input.h"
#include "GLFW/glfw3.h"
#include "imguiFileChooser/ImGuiFileDialog.h"

namespace Gray
{
	MaterialEditor::MaterialEditor()
		: selectedIndex(-1),
		  matList_ptr(nullptr)
	{

	}

	void MaterialEditor::SetMaterialList(MaterialList& matList)
	{
		matList.Add(Default<Material>(), "Empty");
		paths.emplace_back();
		matList_ptr = &matList;
	}

	void MaterialEditor::DrawUI()
	{
		assert(matList_ptr);
		if (ImGui::Button("Add Material"))
		{
			static int id = 1;
			(*matList_ptr).Add(Material(), "material " + std::to_string(id++));
			paths.emplace_back();
		}

		UISelectionPanel();
		UIRenamePanel();
		UIMaterialPropertiesPanel();
	}

	void MaterialEditor::UISelectionPanel()
	{
		const std::vector<const char*> cnames = (*matList_ptr).GetCNames();
		if (!(cnames.empty()))
		{
			ImGui::ListBox("Materials", &selectedIndex, &cnames[0], static_cast<int>(cnames.size()));
		}
	}

	void MaterialEditor::UIMaterialPropertiesPanel()
	{
		if (selectedIndex >= 0)
		{
			std::vector<Material>& materials = (*matList_ptr).GetMaterials();
			assert(selectedIndex < materials.size());
			Material& selectedMaterial = materials[selectedIndex];

			std::string path;

			{
				std::string& dpath = paths[selectedIndex].diffusePath;
				if(FileChooser(dpath, "Diffuse"))
					selectedMaterial.SetDiffuse(txm.GetTexture(dpath));
			}

			{
				std::string& spath = paths[selectedIndex].specularPath;
				if(FileChooser(spath, "Specular"))
					selectedMaterial.SetDiffuse(txm.GetTexture(spath));
			}

			{
				std::string& epath = paths[selectedIndex].emissionPath;
				if(FileChooser(epath, "Emission"))
					selectedMaterial.SetDiffuse(txm.GetTexture(epath));
			}
		}
	}

	bool FileChooser(std::string& path, const std::string& buttonName)
	{
		bool ret = false;

		if (ImGui::Button(buttonName.c_str()))
		{
			igfd::ImGuiFileDialog::Instance()->OpenDialog(buttonName, "Choose Texture File", "{.png,.jpeg,.jpg}", ".");
		}

		if (igfd::ImGuiFileDialog::Instance()->FileDialog(buttonName))
		{
			if (igfd::ImGuiFileDialog::Instance()->IsOk)
			{
				path = igfd::ImGuiFileDialog::Instance()->GetFilePathName();
				std::replace(path.begin(), path.end(), '\\', '/');

				GRAY_CORE_WARN("Chose file " + path);
				ret = true;
			}

			igfd::ImGuiFileDialog::Instance()->CloseDialog(buttonName);
		}
		

		ImGui::SameLine();
		ImGui::Text(path.c_str());

		return ret;
	}

	void MaterialEditor::UIRenamePanel()
	{
		if (selectedIndex >= 0)
		{
			static char inp[256] = "";
			ImGui::Text("Material Name : ");
			ImGui::SameLine();
			ImGui::InputText("##Name", inp, 255);
			ImGui::SameLine();
			if (ImGui::Button("Rename"))
			{
				std::string nname = std::string(inp);
				(*matList_ptr).ChangeNameAt(static_cast<uint>(selectedIndex), nname);
			}
		}
	}

	void MaterialEditor::OnKeyPressed(const KeyPressedEvent& e)
	{
	}
}