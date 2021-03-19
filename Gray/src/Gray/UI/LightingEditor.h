#pragma once

#include "Platform/Opengl/Shader.h"
#include "Gray/Mesh/Mesh.h"
#include "Gray/Graphics/Light/LightingManager.h"
#include "Gray/Camera/EditorCamera.h"
#include "Gray/Events/KeyEvent.h"
#include "ImGuizmo/ImGuizmo.h"

namespace Gray
{
	class Editor;
	struct Light
	{
		uint ID;
		Gray::LightType ltype;

		friend bool operator<(const Light& l1, const Light& l2)
		{
			return l1.ID < l2.ID;
		}

		friend bool operator==(const Light& l1, const Light& l2)
		{
			return l1.ID == l2.ID;
		}
	};

	class LightingEditor
	{
	public:
		LightingEditor();

		void DrawUI(const Editor& editor);
		const LightingManager& GetLightingManager() const;
		void ShowGlobalLight(bool b);
		void OnEvent(Event& e);

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
		void DeleteSelectedLight();
		void OnLightSelect();
		void DrawPointer(const EditorCamera& camera, const glm::mat4& model);

		void OnKeyPressed(Gray::KeyPressedEvent& e);
	};
}