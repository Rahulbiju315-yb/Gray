#include "grpch.h"

#include "Gizmo.h"

#include "imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Gray/Math/Constants.h"
#include "Gray/Window/Window.h"
#include "Gray/Algo/Search.h"

#include "Platform/Opengl/Renderer.h"
#include "LightingEditor.h"

namespace Gray
{
	const Light GLOBAL_LIGHT = Light{ 0, LightType::PointLight };

	LightingEditor::LightingEditor()
		: selectedLight(GLOBAL_LIGHT),
		  showRendered(false),
		  s_model(UNIT_MAT4),
		  lightMan_ptr(nullptr)
	{
		pointerMesh = Gray::CreateMeshPNT(Gray::GetPyramidMeshData());
		pointerShader->LoadProgram("res/shaders/colorShader.shader");
		pointerShader->SetUniform("color", glm::vec3(1));

	}

	void LightingEditor::DrawUI(const EditorCamera& camera)
	{
		assert(lightMan_ptr);

		UIAddButtons();
		UISelectionPanel();

		if (!showRendered && !(selectedLight == GLOBAL_LIGHT))
		{
			if (Gizmo::GizmoRender(s_model, camera.GetView(), camera.GetProjection()))
			{
				UpdateSelectedLight();
			}
		}

		if ((selectedLight.ltype == Gray::LightType::SpotLight || 
			 selectedLight.ltype == Gray::LightType::DirectionalLight))
		{
			DrawPointer(camera, s_model);
		}
	}

	void LightingEditor::SetLightingManager(LightingManager& lmgr)
	{
		PointLight pl;
		pl.color.ambient = glm::vec3(1);
		lmgr.AddPointLight(pl);
		lightMan_ptr = &lmgr;
	}

	void LightingEditor::DrawPointer(const EditorCamera& camera, const glm::mat4& model)
	{
		pointerShader->SetUniform("projection", camera.GetProjection());
		pointerShader->SetUniform("view", camera.GetView());
		pointerShader->SetUniform("model", glm::scale(model, { 0.25f, 0.5f, 0.25f }));

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Draw(*pointerMesh.va, *pointerMesh.ib, *pointerShader);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void LightingEditor::UISelectionPanel()
	{
		if (!names.empty())
		{
			static bool changed = false;
			static int currentItem = 0;

			std::vector<const char*> cnames;
			cnames.reserve(names.size());
			for (const std::string& s : names)
				cnames.push_back(s.c_str());

			changed = ImGui::ListBox("Items : ", &currentItem, &(cnames[0]), static_cast<int>(names.size()));

			if (changed)
			{
				selectedLight = lights[currentItem];
				OnLightSelect();
			}

		}
	}

	void LightingEditor::UIAddButtons()
	{

		if (ImGui::Button("Add point light"))
		{
			uint i = (*lightMan_ptr).AddPointLight();
			lights.push_back(Light{ i, Gray::LightType::PointLight });
			names.push_back(("Point Light " + std::to_string(i)));
		}

		if (ImGui::Button("Add spot light"))
		{
			uint i = (*lightMan_ptr).AddSpotLight();
			lights.push_back(Light{ i, Gray::LightType::SpotLight });
			names.push_back(("Spot Light " + std::to_string(i)));
		}

		if (ImGui::Button("Add directional light"))
		{
			uint i = (*lightMan_ptr).AddDirectionalLight();
			lights.push_back(Light{ i, Gray::LightType::DirectionalLight });
			names.push_back(("Directional Light " + std::to_string(i)));
		}

	}

	void LightingEditor::UpdateSelectedLight()
	{
		if (selectedLight.ltype == Gray::LightType::PointLight)
		{
			Gray::PointLight& pl = (*lightMan_ptr).GetPointLight(selectedLight.ID);
			pl.pos = glm::vec3(s_model[3]);
		}

		else if (selectedLight.ltype == Gray::LightType::SpotLight)
		{
			Gray::SpotLight& sl = (*lightMan_ptr).GetSpotLight(selectedLight.ID);
			sl.pos = glm::vec3(s_model[3]);
			sl.dir = glm::mat3(s_model) * glm::vec3{ 0, 1, 0 };
		}

		else if (selectedLight.ltype == Gray::LightType::DirectionalLight)
		{
			Gray::DirectionalLight& dl = (*lightMan_ptr).GetDirectionalLight(selectedLight.ID);
			dl.dir = glm::mat3(s_model) * glm::vec3{ 0, 1, 0 };
		}
	}

	void LightingEditor::DeleteSelectedLight()
	{
		int index = Bsearch(lights, selectedLight);
		GRAY_CORE_INFO(std::to_string(index) + " is index");
		assert(index >= 0);

		(*lightMan_ptr).RemoveLight(selectedLight.ID, selectedLight.ltype);
		names.erase(names.begin() + index);
		lights.erase(lights.begin() + index);

		selectedLight = GLOBAL_LIGHT;
	}

	void GetRotationMat(glm::vec3 v1, glm::vec3 v2, glm::mat4& mat)
	{
		glm::vec3 cross = glm::cross(v1, v2);
		float alpha = glm::acos(glm::dot(glm::normalize(v1), glm::normalize(v2)));

		if (alpha != 0)
			mat = glm::rotate(Gray::UNIT_MAT4, alpha, cross);
		else
			mat = UNIT_MAT4;
	}

	void LightingEditor::OnLightSelect()
	{
		if (selectedLight.ltype == Gray::LightType::PointLight)
		{
			Gray::PointLight& pl = (*lightMan_ptr).GetPointLight(selectedLight.ID);
			s_model = glm::translate(Gray::UNIT_MAT4, pl.pos);
		}

		else if (selectedLight.ltype == Gray::LightType::SpotLight)
		{
			Gray::SpotLight& sl = (*lightMan_ptr).GetSpotLight(selectedLight.ID);
			GetRotationMat(glm::vec3{ 0, 1, 0 }, sl.dir, s_model);
			s_model[3] = glm::vec4(sl.pos, 1);
		}

		else if (selectedLight.ltype == Gray::LightType::DirectionalLight)
		{
			Gray::DirectionalLight& dl = (*lightMan_ptr).GetDirectionalLight(selectedLight.ID);
			GetRotationMat({ 0, 1, 0 }, dl.dir, s_model);
		}
	}

	void LightingEditor::OnKeyPressed(const KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == GLFW_KEY_DELETE)
		{
			if (!(selectedLight == GLOBAL_LIGHT))
				DeleteSelectedLight();
		}	
	}

	void LightingEditor::ShowGlobalLight(bool b)
	{
		(*lightMan_ptr).GetPointLight(1).color.ambient = glm::vec3(b ? 1.0f : 0.0f);
	}
}