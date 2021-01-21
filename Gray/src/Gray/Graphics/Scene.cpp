#include "grpch.h"
#include "Scene.h"
#include "Gray/Graphics/Resource/ResourceManager.h"

namespace Gray
{
	Scene::Scene(int renderListCapacity) : camera(Camera()), reloadIndex(-1)
	{
		SetCapacity(renderListCapacity);
	}

		
	void Scene::SetCapacity(int n)
	{
		renderList.reserve(n);
	}

	int Scene::CreateRModel()
	{
		renderList.push_back(RenderableModel());

		return (int)renderList.size() - 1;
	}

	int Scene::CreateLight(LightType type, std::unique_ptr<Source> s)
	{
		int index = lightMan.CreateLight(type);
		lightMan.GetLightSource(index, type).source = std::move(s);

		return index;
	}

	void Scene::SetModelPath(int i, const std::string& path)
	{
		assert(i < renderList.size());
		renderList[i].SetPath(path);
		dirtyModels.push_back(i);

		if (reloadIndex == -1)
			reloadIndex = 0;
	}

	bool Scene::IsSceneComplete()
	{
		return reloadIndex == -1 && Gray::ImageLoadDone();
	}

	RenderableModel& Scene::GetRModel(int i)
	{
		assert(i < renderList.size());
		return renderList[i];
	}

	LightSource& Scene::GetLight(int i, LightType type)
	{
		return lightMan.GetLightSource(i, type);
	}

	Camera& Scene::GetCamera()
	{
		return camera;
	}

	void Scene::SetPerspective(Perspective p)
	{
		camera.SetPerspective(p);
		SetProjectionUniform();
	}

	void Scene::RenderModels()
	{
		LightUpScene();
		SetViewUniforms();
		for (RenderableModel& r : renderList)
			r.Render();
	}

	void Scene::ClearScene()
	{
		renderList.clear();
		lightMan.ClearList();
		unique_shaders.clear();
	}

	void Scene::SetViewUniforms()
	{
		for (const Shared<Shader>& shader : unique_shaders)
		{
			shader->SetUniform("view", camera.GetView());
		}
	}

	void Scene::LightUpScene()
	{
		for (auto& shader : unique_shaders)
		{
			lightMan.SetUniformsFor(*shader);
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

	void Scene::InitForRender()
	{
		ComputeShaderSet();
		SetProjectionUniform();
	}

	void Scene::SetProjectionUniform()
	{
		for (auto shader : unique_shaders)
		{
			shader->SetUniform("projection", camera.GetProjection());
		}
	}

}