#pragma once
#include "Test.h"
#include "Gray/Graphics/Light/LightingManager.h"
#include "Gray/Mesh/Mesh.h"
#include "Gray/Math/Math.h"
#include "Gray/Math/Constants.h"
#include "Gray/UI/Editor.h"
#include "Gray/Resources/ShaderManager.h"
#include "Gray/Camera/CameraController.h"
#include "UniformUtil.h"

namespace Test
{

	class TestEditor : public Test
	{
	public:
		TestEditor()
		{
			shader = shm.GetShader("res/shaders/shader.shader");
			wood->LoadTexture("res/textures/wood.png", true);

			material.SetDiffuse(wood);
			material.SetSpecular(wood);
			material.SetEmission(Gray::EmptyTex());
		}
		
		void OnInit() 
		{ 
		}

		void PreRender(float dt) override
		{
		}

		void Render(float dt) override
		{
			const Gray::EditorCamera& camera = editor.GetEditorCamera();
			shader->SetUniform("view", camera.GetView());
			shader->SetUniform("viewPos", camera.GetPos());
			shader->SetUniform("projection", camera.GetProjection());

			editor.GetLightingManager().SetUniformsFor(*shader);

			const std::vector<Gray::RenderableMesh>& rmeshes = editor.GetRMeshes();
			for (const Gray::RenderableMesh& rmesh : rmeshes)
			{
				shader->SetUniform("model", rmesh.modelMatrix);
				shader->SetUniform("invModel", rmesh.invModelMatrix);
				SetMaterialUniform(material, *shader);

				Gray::Draw(*rmesh.mesh.va, *rmesh.mesh.ib, *shader);
			}
		}

		void PostRender(float dt) override
		{
			editor.Display(dt);
		}

		void OnEvent(Gray::Event& e)
		{
			editor.OnEvent(e);
		}

	private:
		Gray::Editor editor;
		Gray::ShaderManager shm;
		Gray::TextureManager txm;

		Gray::NoCopy<Gray::Texture> wood;
		Gray::Material material;

		Gray::WeakRef<Gray::Shader> shader;
	};
}