#pragma once

#include "Model/RenderableModel.h"
#include "Light/LightSource.h"
#include "Camera.h"
#include "RenderList.h"
#include "LightingManager.h"
#include "Platform/Opengl/Shader.h"

namespace Gray
{
	struct SharedShaderComp
	{
		bool operator()(const Shared<Shader>& first, const Shared<Shader>& second) const
		{
			return first->GetID() < second->GetID();
		}
	};
	typedef void(*OnLoad)(RenderableModel& rmodel);

	class Scene
	{

	public:

		Scene(int renderListCapacity);

		Camera& GetCamera();

		int CreateRModel();
		int CreateLight(LightType type, std::unique_ptr<Source> s);

		void SetModelPath(int i, const std::string& path);
		bool IsSceneComplete();

		template<class T>
		bool LoadResources(T& onLoadCallback)
		{
			if (reloadIndex == -1)
				return true;

			assert(reloadIndex < dirtyModels.size());
			assert(dirtyModels[reloadIndex] < renderList.size());

			int rindex = dirtyModels[reloadIndex];
			RenderableModel& rmodel = renderList[rindex];
			if (rmodel.TryToLoadModel())
			{
				onLoadCallback.OnLoad(rmodel, rindex);
				reloadIndex++;
				if (reloadIndex == dirtyModels.size())
				{
					reloadIndex = -1;
					dirtyModels.clear();
					return true;
				}
			}

			return false;
		}

		template<class T>
		void ReloadRModels(T& onLoadCallback)
		{
			for (int i = 0; i < renderList.size(); i++)
			{
				onLoadCallback.OnLoad(renderList[i], i);
			}
		}

		void ComputeShaderSet();
		void InitForRender();

		RenderableModel& GetRModel(int i);
		LightSource& GetLight(int i, LightType type);

		void RenderModels();
		void SetPerspective(Perspective p);

		void ClearScene();
		void SetCapacity(int n);

	private:

		Camera camera;
		LightingManager lightMan;
		std::vector<RenderableModel> renderList;

		std::vector<int> dirtyModels;
		int reloadIndex;

		std::set<Shared<Shader>, SharedShaderComp> unique_shaders;


		void LightUpScene();
		void SetViewUniforms();
		void SetProjectionUniform();

	};

}