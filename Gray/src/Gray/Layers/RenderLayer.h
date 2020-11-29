#pragma once

#include "Layer.h"

#include "Gray/Graphics/Renderable.h"
#include "Gray/Graphics/Camera.h"
#include "Gray/Graphics/LightSource.h"

//Layer for debug purposes.
namespace Gray
{
	typedef void (*ForEachRenderableFunction)(Renderable* , void*);

	class RenderLayer : public Layer
	{
	public:
		RenderLayer();
		~RenderLayer();

		void OnAttatch() override;
		void OnDetatch() override;

		void AddRenderable(std::shared_ptr<Renderable> r);
		void RemoveRenderable(std::shared_ptr<Renderable> r);

		std::shared_ptr<Renderable> RenderableAt(int i);
		
		void OnUpdate() override;
		
		void SetCameraMovementEnabled(bool en);
		bool GetCameraMovementEnabled();
		
		void SetCameraLookAroundEnabled(bool en);
		bool GetCameraLookAroundEnabled();

		void OnImguiRender() override;

		void SetCameraPos(glm::vec3 pos);
		const glm::vec3& GetCameraPos();

		void SetCameraDir(glm::vec2 dir);
		const glm::vec2& GetCameraDir();


		void OnMouseMoved(MouseMovedEvent& e) override;

		void ForEach(ForEachRenderableFunction func);
		void SetForEachData(void* data);
		void* GetForEachData();

	private:
		std::vector<std::shared_ptr<Renderable>> renderList;
		std::vector<std::shared_ptr<LightSource>> lightSources;
		std::set<Shader*> unique_shaders;

		Camera camera;
		bool cameraMovEn;
		bool cameraLookEn;
		glm::mat4 projection;

		void* data;
	};
}