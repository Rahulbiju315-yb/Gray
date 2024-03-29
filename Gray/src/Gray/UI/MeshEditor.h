#pragma once

#include "glm/glm.hpp"
#include "Gray/Camera/EditorCamera.h"
#include "Gray/Mesh/Mesh.h"

#include "Gray/Events/KeyEvent.h"
#include "Gray/Resources/TextureManager.h"
#include "Scene.h"

namespace Gray
{
	class Editor;

	class MeshEditor
	{
	public:
		MeshEditor();
		void DrawUI(const EditorCamera& camera, SceneInfo& scene);
		void OnKeyPressed(const KeyPressedEvent& e, SceneInfo& scene);

	private:
		void UIAddButtons();
		void UIMeshSelectionPanel();
		void UIMaterialSelectionPanel();

		TextureManager txm;
		std::vector<uint> meshDataID;
		std::vector<MeshData> meshData;
		std::vector<std::string> names;
		std::vector<const char*> cnames;

		int selectedMeshIndex;
		int selectedMatIndex;
	};
}