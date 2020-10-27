#pragma once

#include "Layer.h"
#include "Gray/Graphics/Renderable.h"
#include "Gray/Graphics/Camera.h"

//Layer for debug purposes.
namespace Gray
{
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

	private:
		std::vector<Renderable*> renderList;
		bool cameraMovEn;
		bool cameraLookEn;
		Camera* camera;
	};
}