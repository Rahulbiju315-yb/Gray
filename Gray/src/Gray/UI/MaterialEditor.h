#pragma once

#include "Gray/Events/KeyEvent.h"
#include "Gray/Graphics/Material.h"
#include "Gray/Resources/TextureManager.h"
#include "Scene.h"

namespace Gray
{
	bool FileChooser(std::string& path, const std::string& name);

	struct MaterialTexturePaths
	{
		MaterialTexturePaths()
		{
			diffusePath = "Empty";
			specularPath = "Empty";
		    emissionPath = "Empty";
		}

		std::string diffusePath;
		std::string specularPath;
		std::string emissionPath;
	};

	class Editor;
	class MaterialEditor
	{
	public:
		MaterialEditor();
		void SetMaterialList(MaterialList& matList);
		void DrawUI();
		
		void OnKeyPressed(const KeyPressedEvent& e);

	private:
		TextureManager txm;
		MaterialList* matList_ptr;
		std::vector<MaterialTexturePaths> paths;

		int selectedIndex;

		void UISelectionPanel();
		void UIMaterialPropertiesPanel();
		void UIRenamePanel();
	};
}