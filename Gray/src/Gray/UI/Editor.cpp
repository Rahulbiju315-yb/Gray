#include "grpch.h"
#include "Editor.h"
#include "Gray/Window/Window.h"
#include "Gray/Camera/CameraController.h"
#include "Gray/Resources/GlobalRM.h"
#include "Gray/Math/Constants.h"
#include "Platform/Opengl/Renderer.h"

namespace Gray
{
	Editor::Editor()
		: ops(ImGuizmo::TRANSLATE),
	      showRendered(false), showDemo(false)
	{

	}

	NoCopyMesh GetQuadPlane(uint w, uint h, float d)
	{
		std::vector<float> vertices;

		for (int i = 0; i < w; i++)
		{
			float x = i * d;
			vertices.push_back(x);
			vertices.push_back(0);
			vertices.push_back(0);

			vertices.push_back(x);
			vertices.push_back(0);
			vertices.push_back(h);
		}

		for (int i = 0; i < h; i++)
		{
			float z = i * d;
			vertices.push_back(0);
			vertices.push_back(0);
			vertices.push_back(z);

			vertices.push_back(w);
			vertices.push_back(0);
			vertices.push_back(z);
		}
		
		NoCopyMesh mesh;
		mesh.vb->LoadBufferData(&(vertices[0]), vertices.size() * sizeof(float));

		BufferLayout bl;
		bl.Push<float>(3);

		mesh.va->SetAttribPointers(*mesh.vb, bl);
        return std::move(mesh);
	}

	void DrawGrid(const glm::mat4& view, const glm::mat4& proj)
	{
		static WeakRef<Shader> shader = GlobalRM::shaderManager.GetShader("res/shaders/gridShader.shader");
		static NoCopyMesh mesh = GetQuadPlane(100, 100, 1.0f);

		glm::mat4 model = UNIT_MAT4;
		model[3] = { -50, 0, -50, 1 };
		shader->SetUniform("model", model);
		shader->SetUniform("view", view);
		shader->SetUniform("projection", proj);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		shader->Bind();
		mesh.va->Bind();
		glDrawArrays(GL_LINES, 0, 400);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void Editor::Display(float dt)
	{
		CameraController::Control(camera, dt);
		if (!showRendered)
		{
			UIDrawTab();
			UIEditor();
			ImGuiIO& io = ImGui::GetIO();
			ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
			ImGuizmo::SetOrthographic(false);
			DrawGrid(camera.GetView(), camera.GetProjection());
		}
	}

	bool Editor::GizmoRender(glm::mat4& model) const
	{
		bool manipulated = ImGuizmo::Manipulate(&(camera.GetView()[0][0]), &(camera.GetProjection()[0][0]),
			ops, ImGuizmo::WORLD, &(model[0][0]), nullptr, nullptr, nullptr, nullptr);

		return manipulated;
	}

	void Editor::OnEvent(Event& e)
	{
		EventType type = e.GetType();
		if (type == EventType::KeyPressed)
			OnKeyPressed(static_cast<KeyPressedEvent&>(e));

		if (selectedEType == EditorType::Light)
			lEdit.OnEvent(e);

		else if (selectedEType == EditorType::Mesh)
			mEdit.OnEvent(e);
	}

	const EditorCamera& Editor::GetEditorCamera() const
	{
		return camera;
	}

	const LightingManager& Editor::GetLightingManager() const
	{
		return lEdit.GetLightingManager();
	}

	const std::vector<RenderableMesh>& Editor::GetRMeshes() const
	{
		return mEdit.GetRMeshes();
	}

	void Editor::OnKeyPressed(const KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == GLFW_KEY_T)
		{
			Window::SetCursorEnabled(!Window::IsCursorEnabled());
		}

		else if (e.GetKeyCode() == GLFW_KEY_R)
		{
			showRendered = !showRendered;
			lEdit.ShowGlobalLight(!showRendered);
		}
		

		else if (e.GetKeyCode() == GLFW_KEY_Z)
		{
			ops = ImGuizmo::TRANSLATE;
		}

		else if (e.GetKeyCode() == GLFW_KEY_X)
		{
			ops = ImGuizmo::ROTATE;
		}

		else if (e.GetKeyCode() == GLFW_KEY_C)
		{
			ops = ImGuizmo::SCALE;
		}

	}

	void Editor::UIDrawTab()
	{
		if (ImGui::Button("Light"))
		{
			selectedEType = EditorType::Light;
		}
		
		ImGui::SameLine();

		if (ImGui::Button("Mesh"))
		{
			selectedEType = EditorType::Mesh;
		}
	}

	void Editor::UIEditor()
	{
		if (selectedEType == EditorType::Light)
		{
			lEdit.DrawUI(*this);
		}

		else if (selectedEType == EditorType::Mesh)
		{
			mEdit.DrawUI(*this);
		}
	}
}
