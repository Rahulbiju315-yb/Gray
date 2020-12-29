#pragma once

#include "Model/RenderableModel.h"
#include "Light/LightSource.h"
#include "Camera.h"
#include "RenderList.h"
#include "LightingManager.h"
#include "Platform/Opengl/Shader.h"

namespace Gray
{
	class Scene
	{
		typedef void (*ForEachRenderableFunction)(Renderable* , void*);

	public:

		Scene(int renderListCapacity);

		Camera* GetCamera();

		std::vector<RenderableModel>::iterator begin();
		std::vector<RenderableModel>::iterator end();

		RenderableModel* CreateRenderModel();
		LightSource* CreateLight(LightType type, std::unique_ptr<Source> s);

		LightingManager* GetLightingManager();
		RenderList* GetRenderList();
		const std::set<Shader*>& GetShaderSet();

		void LightUpScene();
		void SetViewUniform();
		void SetView(const glm::mat4& view);

		void ComputeShaderSet();
		void SetProjectionUniform();

	private:
		RenderList renderList;
		LightingManager lightMan;
		std::set<Shader*> unique_shaders;

		Camera camera;
		bool validShaderSet;
		bool validProjection;
	};

}