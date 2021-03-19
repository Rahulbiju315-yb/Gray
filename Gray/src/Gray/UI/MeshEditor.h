#pragma once

#include "glm/glm.hpp"
#include "Gray/Camera/EditorCamera.h"
#include "Gray/Mesh/Mesh.h"

#include "Gray/Events/KeyEvent.h"
#include "Gray/Resources/TextureManager.h"

namespace Gray
{
	class Editor;
	class MeshEditor
	{
	public:
		MeshEditor();
		void DrawUI(const Editor& editor);
		const std::vector<RenderableMesh>& GetRMeshes() const;

		void OnEvent(Event& e);

	private:
		void UIAddButtons();
		void UISelectionPanel();
		void OnKeyPressed(KeyPressedEvent& e);

		TextureManager txm;
		std::vector<RenderableMesh> rmeshes;
		std::vector<uint> meshDataID;
		std::vector<std::string> names;

		std::vector<MeshData> meshData;

		int selectedIndex;
	};
}