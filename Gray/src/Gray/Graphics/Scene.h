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
	class Scene
	{

	public:

		Scene(int renderListCapacity);

		Camera* GetCamera();

		std::vector<RenderableModel>::iterator begin();
		std::vector<RenderableModel>::iterator end();

		RenderableModel* CreateRenderModel();
		LightSource* CreateLight(LightType type, std::unique_ptr<Source> s);

		LightingManager* GetLightingManager();
		RenderList* GetRenderList();
		const std::set<Shared<Shader>, SharedShaderComp>& GetShaderSet();

		void LightUpScene();
		void SetViewUniform();
		void SetView(const glm::mat4& view);

		void ComputeShaderSet();
		void SetProjectionUniform();

		void ClearScene();
		void SetCapacity(int n);

	private:
		RenderList renderList;
		LightingManager lightMan;
		std::set<Shared<Shader>, SharedShaderComp> unique_shaders;

		Camera camera;
		bool validShaderSet;
		bool validProjection;
	};

}