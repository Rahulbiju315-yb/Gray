#include "grpch.h"
#include "Scene.h"

namespace Gray
{
	Scene::Scene(int renderListCapacity) : camera(this), validProjection(false), validShaderSet(false)
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
		validShaderSet = false;
		validProjection = false;

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

	const std::set<Shader*>& Scene::GetShaderSet()
	{
		return unique_shaders;
	}

	void Scene::LightUpScene()
	{
		for (auto shader : unique_shaders)
		{
			lightMan.SetUniformsFor(*shader);
		}
	}

	void Scene::SetViewUniform()
	{
		for (auto shader : unique_shaders)
		{
			camera.SetViewUniformsFor(shader);
		}
	}

	void Scene::SetView(const glm::mat4& view)
	{
		for (auto shader : unique_shaders)
		{
			shader->SetUniform("view", view);
		}
	}

	void Scene::ComputeShaderSet()
	{
		if (!validShaderSet)
		{
			for (auto& renderable : renderList)
			{
				unique_shaders.insert(renderable.GetShader().get());
			}

			validShaderSet = true;
		}
	}

	void Scene::SetProjectionUniform()
	{
		if (!validProjection)
		{
			for (auto shader : unique_shaders)
			{
				shader->SetUniform("projection", camera.GetProjection());
			}
			validProjection = true;
		}
	}
}