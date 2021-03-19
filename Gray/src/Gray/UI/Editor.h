#pragma once

#include "LightingEditor.h"
#include "MeshEditor.h"
#include "ImGuizmo/ImGuizmo.h"
#include "Gray/Events/KeyEvent.h"
#include "Gray/Camera/EditorCamera.h"

namespace Gray
{
	class Editor
	{
	public:
		Editor();
		void Display(float dt);
		void OnEvent(Event& e);

		bool GizmoRender(glm::mat4& model) const;		
		const EditorCamera& GetEditorCamera() const;

		const LightingManager& GetLightingManager() const;
		const std::vector<RenderableMesh>& GetRMeshes() const;

	private:
		enum class EditorType
		{
			Mesh,
			Light
		};

		EditorCamera camera;
		MeshEditor mEdit;
		LightingEditor lEdit;
		EditorType selectedEType;


		ImGuizmo::OPERATION ops;
		bool showRendered;
		void OnKeyPressed(const KeyPressedEvent& e);
		void UIDrawTab();
		void UIEditor();
	};
}