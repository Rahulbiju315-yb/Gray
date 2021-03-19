#pragma once
#include "Test.h"
#include "Gray/Graphics/Light/LightingManager.h"
#include "Gray/Mesh/Mesh.h"
#include "ImGuizmo/ImGuizmo.h"
#include "Gray/Camera/SceneCamera.h"
#include "Gray/Camera/CameraController.h"
#include "Gray/Math/Math.h"
#include "Gray/Math/Constants.h"
#include "Gray/UI/LightingEditor.h"

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

			diffuse->LoadTexture("res/textures/wood.png", true);
			specular->LoadTexture("res/textures/wood.png", true);
			emission->LoadTexture("res/textures/wood.png", true);
			empty->LoadEmptyTexture(1, 1);

			shader->LoadProgram("res/shaders/shader.shader");
			shader->SetUniform("material.diffuse", 1);
			shader->SetUniform("material.specular", 2);
			shader->SetUniform("material.emission", 3);
			shader->SetUniform("material.shininess", 32.0f);

			diffuse->Bind(1);
			specular->Bind(2);
			empty->Bind(3);
			
			shader->SetUniform("projection", camera.GetProjection());

			shader->SetUniform("model", Gray::UNIT_MAT4);
			shader->SetUniform("invModel", Gray::UNIT_MAT4);

		}
		
		void OnInit() 
		{ 
		}

		void PreRender(float dt) override
		{
		}

		void Render(float dt) override
		{
			shader->SetUniform("view", camera.GetView());
			shader->SetUniform("viewPos", camera.GetPos());

			editor.GetLightingManager().SetUniformsFor(*shader);
			Gray::Draw(*mesh.va, *mesh.ib, *shader);
		}

		void PostRender(float dt) override
		{
			glDepthFunc(GL_ALWAYS);
			Gray::CameraController::Control(camera, dt);
			//editor.DrawUI(camera);
			glDepthFunc(GL_LESS);
		}

		void OnEvent(Gray::Event& e, Gray::EventType type)
		{
			editor.OnEvent(e, type);
		}

	private:
		Gray::LightingEditor editor;
		Gray::EditorCamera camera;

		Gray::NoCopy<Gray::Texture> diffuse;
		Gray::NoCopy<Gray::Texture> specular;
		Gray::NoCopy<Gray::Texture> emission;
		Gray::NoCopy<Gray::Texture> empty;

		Gray::NoCopy<Gray::Shader> shader;

		Gray::NoCopyMesh mesh;
	};
}