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
		}
		
		void OnInit() 
		{ 
		}

		void PreRender(float dt) override
		{
		}

		void Render(float dt) override
		{
			Gray::Scene& sc = editor.GetScene();

			Gray::TextureManager::InitIfRequired();
			const Gray::EditorCamera& camera = editor.GetEditorCamera();
			shader->SetUniform("view", camera.GetView());
			shader->SetUniform("viewPos", camera.GetPos());
			shader->SetUniform("projection", camera.GetProjection());

			sc.lightMan.SetUniformsFor(*shader);

			for (const Gray::RenderableMesh& rmesh : sc.rmeshes)
			{
				shader->SetUniform("model", rmesh.modelMatrix);
				shader->SetUniform("invModel", rmesh.invModelMatrix);
				SetMaterialUniform(rmesh.material, *shader);

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

		Gray::WeakRef<Gray::Shader> shader;
	};
}