#pragma once

#include "Layer.h"

#include "Gray/Graphics/Renderable.h"
#include "Gray/Graphics/Camera.h"
#include "Gray/Graphics/LightSourceOpengl.h"

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

		void AddRenderable(Renderable* r);
		void RemoveRenderable(Renderable* r);

		Renderable* RenderableAt(int i);
		
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
		
		void SetLightColor(glm::vec3 color);
		const glm::vec3& GetLightColor();

		void OnMouseMoved(MouseMovedEvent& e) override;

		void ForEach(ForEachRenderableFunction func);
		void SetForEachData(void* data);
		void* GetForEachData();

	private:
		std::vector<Renderable*> renderList;
		bool cameraMovEn;
		bool cameraLookEn;

		Camera* camera;
		LightSourceOpengl* lightSource;

		glm::mat4 projection;

		void* data;
	};
}