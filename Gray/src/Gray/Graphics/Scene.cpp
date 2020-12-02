#include "grpch.h"
#include "Scene.h"

namespace Gray
{
	Scene::Scene() : camera(this)
	{

	}

	Camera* Scene::GetCamera()
	{
		return &camera;
	}

	std::vector<SharedRenderable>::iterator Scene::begin()
	{
		return renderList.begin();
	}

	std::vector<SharedRenderable>::iterator Scene::end()
	{
		return renderList.end();
	}

	std::vector<std::shared_ptr<LightSource>>::iterator Scene::lightsBegin()
	{
		return lightMan.begin();
	}

	std::vector<std::shared_ptr<LightSource>>::iterator Scene::lightsEnd()
	{
		return lightMan.end();
	}

	std::set<Shader*>::iterator Scene::shaderBegin()
	{
		return unique_shaders.begin();
	}

	std::set<Shader*>::iterator Scene::shaderEnd()
	{
		return unique_shaders.end();
	}

	void Scene::Add(SharedRenderable renderable)
	{
		static glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
		renderable->GetShader()->SetUniform("projection", projection);

		renderList.AddRenderable(renderable);
		unique_shaders.insert(renderable->GetShader().get());
	}

	void Scene::Add(SharedLightSource lightSource)
	{
		lightMan.AddLight(lightSource);
	}

	LightingManager* Scene::GetLightingManager()
	{
		return &lightMan;
	}

	RenderList* Scene::GetRenderList()
	{
		return &renderList;
	}

	void Scene::LightUpScene()
	{
		auto [countPointLights, countDirLights, countSpotLights] = lightMan.GetLightCounts();
		for (auto shader : unique_shaders)
		{
			shader->SetUniform("nrOfPointLights", countPointLights);
			shader->SetUniform("nrOfDirectionalLights", countDirLights);
			shader->SetUniform("nrOfSpotLights", countSpotLights);

			for (auto light : lightMan)
			{
				light->SetUniformsFor(shader);
			}
		}
	}

	void Scene::SetView()
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
}