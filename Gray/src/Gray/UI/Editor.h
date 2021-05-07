#pragma once

#include "LightingEditor.h"
#include "MeshEditor.h"
#include "MaterialEditor.h"

#include "Gray/Events/KeyEvent.h"
#include "Gray/Camera/EditorCamera.h"
#include "Gizmo.h"
#include "Scene.h"

#include "Gray/Resources/TextureManager.h"
#include "Gray/Resources/ShaderManager.h"

namespace Gray
{
	struct ResourceManager
	{
		TextureManager txm;
		ShaderManager shm;
	};

	class Editor
	{
	public:
		Editor();

		void Display(float dt);
		void OnEvent(Event& e);


		const EditorCamera& GetEditorCamera() const;
	private:
		enum class EditorType
		{
			Mesh,
			Light,
			Material
		};

		SceneInfo scene;
		EditorCamera camera;

		MeshEditor mEdit;
		LightingEditor lEdit;
		MaterialEditor matEdit;
		EditorType selectedEType;

		ImGuizmo::OPERATION ops;
		bool showRendered;
		bool isAnyWindowFocussed;

		void OnKeyPressed(const KeyPressedEvent& e);
		void UIDrawTab();
		void UIEditor();
	};
}