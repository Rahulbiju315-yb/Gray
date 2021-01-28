#pragma once
#include "Test.h"
#include "Gray/Graphics/Light/LightingManager.h"
#include "Gray/Mesh/Mesh.h"

namespace Test
{
	class TestLighting : public Test
	{
	public:
		TestLighting()
		{
			mesh = Gray::CreateMeshPNT(Gray::GetUnitCube2MeshdData());
			
			diffuse->LoadTexture("res/textures/wood.png", true);
			specular->LoadTexture("res/textures/wood.png", true);
			//emission->LoadTexture("res/textures/wood.png", true);
			emission->LoadEmptyTexture(1, 1);


			shader->LoadProgram("res/shaders/shader.shader");
			shader->SetUniform("material.diffuse", 1);
			shader->SetUniform("material.specular", 2);
			shader->SetUniform("material.emission", 3);
			shader->SetUniform("material.shininess", 32.0f);

			diffuse->Bind(1);
			specular->Bind(2);
			emission->Bind(3);

			shader->SetUniform("projection", camera.GetProjection());

			
			Gray::SpotLight pl1;
			Gray::SpotLight pl2;
			Gray::SpotLight pl3;
			Gray::SpotLight pl4;
			Gray::SpotLight pl5;
			Gray::SpotLight pl6;

			pl1.pos = glm::vec3(0, 0, 2);
			pl1.dir = glm::vec3(0, 0, -2);

			pl2.pos = glm::vec3(-2, 0, 0);
			pl2.dir = glm::vec3(2, 0, 0);

			pl3.pos = glm::vec3(0, 0, -2);
			pl3.dir = glm::vec3(0, 0, 2);

			pl4.pos = glm::vec3(2, 0, 0);
			pl4.dir = glm::vec3(-2, 0, 0);

			pl5.pos = glm::vec3(0, 2, 0);
			pl6.dir = glm::vec3(0, -2, 0);

			lightMan.AddSpotLight(pl1);
			lightMan.AddSpotLight(pl2);
			lightMan.AddSpotLight(pl3);
			lightMan.AddSpotLight(pl4);
			lightMan.AddSpotLight(pl5);
			lightMan.AddSpotLight(pl6);

			cursorEn = true;

			shader->SetUniform("model", glm::mat4(1));
			shader->SetUniform("invModel", glm::mat4(1));
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
			if (ImGui::Button("Add point light"))
			{
				uint i = lightMan.AddPointLight();
				lightsIDs.push_back(i);
				names.push_back(("Point Light " + std::to_string(i)).c_str());
			}

			if (ImGui::Button("Add spot light"))
			{
				uint i = lightMan.AddSpotLight();
				lightsIDs.push_back(i);
				names.push_back(("Spot Light " + std::to_string(i)).c_str());
			}

			if (ImGui::Button("Add directional light"))
			{
				uint i = lightMan.AddDirectionalLight();
				lightsIDs.push_back(i);
				names.push_back(("Directional Light " + std::to_string(i)).c_str());
			}

			if (names.size() > 0)
			{
				static int currentItem = 0;
				ImGui::ListBox("Items : ", &currentItem, &names[0], names.size());
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
		}
	private:
		Gray::Camera camera;
		Gray::LightingManager lightMan;

		std::vector<uint> lightsIDs;
		std::vector<const char*> names;

		Gray::NoCopy<Gray::Texture> diffuse;
		Gray::NoCopy<Gray::Texture> specular;
		Gray::NoCopy<Gray::Texture> emission;

		Gray::NoCopy<Gray::Shader> shader;
		Gray::NoCopyMesh mesh;

		bool cursorEn;
	};
}