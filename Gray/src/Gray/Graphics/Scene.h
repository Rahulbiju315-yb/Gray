#pragma once

#include "Renderable.h"
#include "LightSource.h"
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

		Scene();

		Camera* GetCamera();

		std::vector<SharedRenderable>::iterator begin();
		std::vector<SharedRenderable>::iterator end();
		
		std::vector<SharedLightSource>::iterator lightsBegin();
		std::vector<SharedLightSource>::iterator lightsEnd();

		std::set<Shader*>::iterator shaderBegin();
		std::set<Shader*>::iterator shaderEnd();

		void Add(SharedRenderable renderable);
		void Add(SharedLightSource lightSource);

		LightingManager* GetLightingManager();
		RenderList* GetRenderList();

		void LightUpScene();
		void SetView();
		void SetView(const glm::mat4& view);

	private:
		RenderList renderList;
		LightingManager lightMan;
		std::set<Shader*> unique_shaders;

		Camera camera;
		
	};
}