#pragma once

#include "Layer.h"

#include "Gray/Graphics/Renderable.h"
#include "Gray/Graphics/Camera.h"
#include "Gray/Graphics/LightSource.h"
#include "Gray/Graphics/Scene.h"

//Layer for debug purposes.
namespace Gray
{

	class RenderLayer : public Layer
	{
	public:
		RenderLayer(std::shared_ptr<Scene> scene);
		RenderLayer();

		void SetScene(std::shared_ptr<Scene> scene);

		void OnAttatch() override;
		void OnDetatch() override;
		void OnUpdate() override;	

		void OnImguiRender() override;

		void OnMouseMoved(MouseMovedEvent& e) override;
	private:

		std::shared_ptr<Scene> scene;
	};
}