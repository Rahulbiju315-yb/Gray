#include "grpch.h"
#include "Scene.h"

namespace Gray
{
	Scene::Scene(int renderListCapacity) : camera(Camera())
	{
		renderList.SetCapacity(renderListCapacity);
	}

	Camera* Scene::GetCamera()
	{
		return &camera;
	}

	std::vector<RenderableModel>::iterator Scene::begin()
	{
		return renderList.begin();
	}

	std::vector<RenderableModel>::iterator Scene::end()
	{
		return renderList.end();
	}

	RenderableModel* Scene::CreateRenderModel()
	{
		auto renderable = renderList.CreateRenderModel();
		return renderable;
	}

	LightSource* Scene::CreateLight(LightType type, std::unique_ptr<Source> s)
	{
		LightSource* ls = lightMan.CreateLight(type);
		ls->source = std::move(s);

		return ls;
	}

	LightingManager* Scene::GetLightingManager()
	{
		return &lightMan;
	}

	RenderList* Scene::GetRenderList()
	{
		return &renderList;
	}

	const std::set<Shared<Shader>, SharedShaderComp>& Scene::GetShaderSet()
	{
		return unique_shaders;
	}

	void Scene::LightUpScene()
	{
		for (auto& shader : unique_shaders)
		{
			lightMan.SetUniformsFor(*shader);
		}
	}

	void Scene::RenderModels()
	{
		LightUpScene();
		SetViewUniforms();
		for (RenderableModel& r : renderList)
			r.Render();
	}

	void Scene::SetViewUniforms()
	{
		for (const Shared<Shader>& shader : unique_shaders)
		{
			shader->SetUniform("view", camera.GetView());
		}
	}

	void Scene::ComputeShaderSet()
	{
		unique_shaders.clear();

		for (auto& renderable : renderList)
		{
			unique_shaders.insert(renderable.GetShader());
		}
	}

	void Scene::SetProjectionUniform()
	{
		for (auto shader : unique_shaders)
		{
			shader->SetUniform("projection", camera.GetProjection());
		}
	}

	void Scene::SetPerspective(Perspective p)
	{
		camera.SetPerspective(p);
		SetProjectionUniform();
	}

	void Scene::SetCapacity(int n)
	{
		renderList.SetCapacity(n);
	}

	void Scene::ClearScene()
	{
		renderList.ClearList();
		lightMan.ClearList();
		unique_shaders.clear();
	}
}