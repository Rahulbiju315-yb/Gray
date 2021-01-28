#pragma once
#include "Test.h"
#include "Gray/Graphics/Light/LightingManager.h"
#include "Gray/Mesh/Mesh.h"
#include "ImGuizmo/ImGuizmo.h"

namespace Test
{

	struct Light
	{
		uint ID;
		Gray::LightType ltype;
	};

	class TestLighting : public Test
	{
	public:
		TestLighting()
		{
			mesh = Gray::CreateMeshPNT(Gray::GetUnitCube2MeshdData());
			pointer = Gray::CreateMeshPNT(Gray::GetPyramidMeshData());

			diffuse->LoadTexture("res/textures/wood.png", true);
			specular->LoadTexture("res/textures/wood.png", true);
			emission->LoadTexture("res/textures/wood.png", true);
			empty->LoadEmptyTexture(1, 1);

			colorShader->LoadProgram("res/shaders/colorShader.shader");
			colorShader->SetUniform("projection", camera.GetProjection());
			colorShader->SetUniform("color", glm::vec3(1));

			shader->LoadProgram("res/shaders/shader.shader");
			shader->SetUniform("material.diffuse", 1);
			shader->SetUniform("material.specular", 2);
			shader->SetUniform("material.emission", 3);
			shader->SetUniform("material.shininess", 32.0f);

			diffuse->Bind(1);
			specular->Bind(2);
			empty->Bind(3);
			
			shader->SetUniform("projection", camera.GetProjection());

			Gray::PointLight pl;
			pl.color.ambient = glm::vec3(1);
			pl.color.specular = glm::vec3(0.0f);
			pl.color.diffuse = glm::vec3(0.0f);

			lightsIDs.push_back(Light{ lightMan.AddPointLight(pl), Gray::LightType::PointLight });
			names.push_back("Constant");

			cursorEn = true;
			render = false;

			shader->SetUniform("model", glm::mat4(1));
			shader->SetUniform("invModel", glm::mat4(1));

			ops = ImGuizmo::TRANSLATE;
		}
		
		Gray::Scene* OnInit() { return nullptr; }

		void PreRender(float dt) override
		{
			if (!cursorEn)
			{
				camera.Move(dt);
				camera.UpdateLook();
			}
		}

		void Render(float dt) override
		{
			shader->SetUniform("view", camera.GetView());
			shader->SetUniform("viewPos", camera.GetPos());

			lightMan.SetUniformsFor(*shader);

			Gray::Draw(*mesh.va, *mesh.ib, *shader);
		}

		void PostRender(float dt) override
		{
			camera.PostRender();
			DebugAddButtons();
			DebugSelectionPanel();
			static bool changed = false;

			changed = ImGui::Checkbox("Show Rendered Scene", &render);
			if (changed)
			{
				if (!render)
				{
					lightMan.GetPointLight(0).color.ambient = glm::vec3(1);
				}
				else
				{
					lightMan.GetPointLight(0).color.ambient = glm::vec3(0);
				}
			}
			
			if (selectedLight.ltype == Gray::LightType::SpotLight)
			{
				Gray::SpotLight& sl = lightMan.GetSpotLight(selectedLight.ID);
				DrawPointer(s_model);
			}
		}

		void DebugSelectionPanel()
		{
			if (names.size() > 0)
			{
				static bool changed = false;
				static int currentItem = 0;
				static glm::vec3 scale = glm::vec3(1);
				static glm::mat4 unit = glm::mat4(1);

				std::vector<const char*> cnames;
				cnames.reserve(names.size());
				for (const std::string& s : names)
					cnames.push_back(s.c_str());

				changed = ImGui::ListBox("Items : ", &currentItem, &(cnames[0]), names.size());
				selectedLight = lightsIDs[currentItem];

				if (changed)
				{
					if (selectedLight.ltype == Gray::LightType::PointLight)
					{
						Gray::PointLight& pl = lightMan.GetPointLight(selectedLight.ID);
						s_model = glm::translate(unit, pl.pos);
					}

					if (selectedLight.ltype == Gray::LightType::SpotLight)
					{
						Gray::SpotLight& sl = lightMan.GetSpotLight(selectedLight.ID);

						ImGuizmo::RecomposeMatrixFromComponents(&(sl.pos[0]), &(sl.dir[0]), 
							&(scale[0]), &(s_model[0][0]));

					}

				}

				glm::vec3 translation;
				glm::vec3 rotation;

				if (!render)
				{
					GizmoRender(s_model);

					ImGuizmo::DecomposeMatrixToComponents(&(s_model[0][0]), &(translation[0]), &(rotation[0]),
						&(scale[0]));

					if (selectedLight.ltype == Gray::LightType::PointLight)
					{
						Gray::PointLight& pl = lightMan.GetPointLight(selectedLight.ID);
						pl.pos = translation;
					}

					else if (selectedLight.ltype == Gray::LightType::SpotLight)
					{
						Gray::SpotLight& sl = lightMan.GetSpotLight(selectedLight.ID);
						sl.pos = translation;
						sl.dir = rotation;

					}

				}
			}
		}

		void GizmoRender(glm::mat4 & model)
		{
			ImGuiIO& io = ImGui::GetIO();
			ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::DrawGrid(&(camera.GetView()[0][0]), &(camera.GetProjection()[0][0]),
				&(glm::mat4(1)[0][0]), 100.f);

			ImGuizmo::Manipulate(&(camera.GetView()[0][0]), &(camera.GetProjection()[0][0]),
				ops, ImGuizmo::WORLD, &(model[0][0]), nullptr, nullptr, nullptr, nullptr);
		}

		void DebugAddButtons()
		{
			if (ImGui::Button("Add point light"))
			{
				uint i = lightMan.AddPointLight();
				lightsIDs.push_back(Light{ i, Gray::LightType::PointLight });
				names.push_back(("Point Light " + std::to_string(i)));
			}

			if (ImGui::Button("Add spot light"))
			{
				uint i = lightMan.AddSpotLight();
				lightsIDs.push_back(Light{ i, Gray::LightType::SpotLight });
				names.push_back(("Spot Light " + std::to_string(i)));
			}

			if (ImGui::Button("Add directional light"))
			{
				uint i = lightMan.AddDirectionalLight();
				lightsIDs.push_back(Light{ i, Gray::LightType::DirectionalLight });
				names.push_back(("Directional Light " + std::to_string(i)));
			}

		}

		void OnEvent(Gray::Event& e, Gray::EventType type)
		{
			if (type == Gray::EventType::KeyPressed)
				OnKeyPressed((Gray::KeyPressedEvent&)e);
		}

		void OnKeyPressed(Gray::KeyPressedEvent& e)
		{
			if (e.GetKeyCode() == TO_INT(Gray::KeyCodes::Key_T))
			{
				cursorEn = !cursorEn;
				if (cursorEn)
				{
					Gray::TempUtil::EnableCursor();
				}
				else
				{
					Gray::TempUtil::DisableCursor();
				}
			}

			else if (e.GetKeyCode() == TO_INT(Gray::KeyCodes::Key_Z))
			{
				ops = ImGuizmo::TRANSLATE;
			}

			else if (e.GetKeyCode() == TO_INT(Gray::KeyCodes::Key_X))
			{
				ops = ImGuizmo::ROTATE;
			}

			else if (e.GetKeyCode() == TO_INT(Gray::KeyCodes::Key_C))
			{
				ops = ImGuizmo::SCALE;
			}
		}

		void DrawPointer(const glm::mat4& model)
		{
			colorShader->SetUniform("view", camera.GetView());
			colorShader->SetUniform("model", glm::scale(model, { 0.1f, 0.1f, 0.1f }));

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			Gray::Draw(*pointer.va, *pointer.ib, *colorShader);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

	private:
		Gray::Camera camera;
		Gray::LightingManager lightMan;
		glm::mat4 s_model;

		std::vector<Light> lightsIDs;
		std::vector<std::string> names;

		Gray::NoCopy<Gray::Texture> diffuse;
		Gray::NoCopy<Gray::Texture> specular;
		Gray::NoCopy<Gray::Texture> emission;
		Gray::NoCopy<Gray::Texture> empty;

		Gray::NoCopy<Gray::Shader> shader;
		Gray::NoCopy<Gray::Shader> colorShader;

		Gray::NoCopyMesh mesh;
		Gray::NoCopyMesh pointer;

		Light selectedLight;

		ImGuizmo::OPERATION ops;
		bool cursorEn;
		bool render;
	};
}