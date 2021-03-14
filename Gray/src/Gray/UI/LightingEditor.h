#pragma once
#include "Platform/Opengl/Shader.h"

#include "Gray/Mesh/Mesh.h"
#include "Gray/Graphics/Light/LightingManager.h"
#include "Gray/Camera/EditorCamera.h"
#include "Gray/Events/KeyEvent.h"

#include "ImGuizmo/ImGuizmo.h"
#include "Gray/Events/EventListener.h"

namespace Gray
{
	struct Light
	{
		uint ID;
		Gray::LightType ltype;
	};

	class LightingEditor : public EventListener
	{
	public:
		LightingEditor();

		void DrawEditor(const EditorCamera& camera);
		const LightingManager& GetLightingManager() const;
		void OnEvent(Event& e, EventType type) override;

	private:
		glm::mat4 s_model;
		NoCopy<Shader> pointerShader;
		NoCopyMesh pointerMesh;

		LightingManager lightMan;
		std::vector<Light> lights; //Lights added to scene
		std::vector<std::string> names; //Names of the light objects

		Light selectedLight;
		ImGuizmo::OPERATION ops;
		bool showRendered;

		void UISelectionPanel();
		void UIAddButtons();
		void UpdateSelectedLight();
		void GizmoRender(glm::mat4& model, const EditorCamera& camera);
		void OnLightSelect();
		void DrawPointer(const EditorCamera camera, const glm::mat4& model);

		void OnKeyPressed(Gray::KeyPressedEvent& e);
	};
}