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


	void Scene::SetModelPath(int i, const std::string& path)
	{
		assert(i < renderList.size());
		bool requiredToLoadModel = renderList[i].SetPath(path);
		
		if (requiredToLoadModel)
		{
			dirtyModels.push_back(i);

			if (reloadIndex == -1)
				reloadIndex = 0;
		}
	}

	bool Scene::IsSceneComplete()
	{
		return reloadIndex == -1 && Gray::RM_ImageLoadDone();
	}

	RenderableModel& Scene::GetRModel(int i)
	{
		assert(i < renderList.size());
		return renderList[i];
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

		// View uniform
		for (const Shared<Shader>& shader : unique_shaders)
		{
			shader->SetUniform("view", camera.GetView());
		}

		// viewPos
		for (const Shared<Shader>& shader : unique_shaders)
		{
			shader->SetUniform("viewPos", camera.GetPos());
		}

		for (RenderableModel& r : renderList)
			r.Render();
	}

	void Scene::ClearScene()
	{
		renderList.clear();

		RM_FinishModelLoad();
		RM_ClearModelLoadList();

		dirtyModels.clear();

		unique_shaders.clear();
	}

	void Scene::SetViewUniforms()
	{

	}

	void Scene::LightUpScene()
	{
		for (auto& shader : unique_shaders)
		{
		
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