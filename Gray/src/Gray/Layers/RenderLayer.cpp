#include "grpch.h"
#include "RenderLayer.h"

namespace Gray
{
	RenderLayer::RenderLayer()
	{

	}

	void RenderLayer::OnAttatch()
	{

	}

	void RenderLayer::AddRenderable(Renderable* r)
	{
		renderList.push_back(r);
	}

	void RenderLayer::RemoveRenderable(Renderable* r)
	{
		std::remove(renderList.begin(), renderList.end(), r);
	}

	Renderable* RenderLayer::RenderableAt(int i)
	{
		return renderList.at(i);
	}

	void RenderLayer::OnUpdate()
	{
		Layer::OnUpdate();

		for (Renderable* renderable : renderList)
		{
			if (renderable->GetRenderEnabled())
				renderable->OnUpdate(dt);
		}
	}

	void RenderLayer::SetCameraMovementEnabled(bool en)
	{
		cameraMovEn = en;
	}

	bool RenderLayer::GetCameraMovementEnabled()
	{
		return cameraLookEn;
	}

	void RenderLayer::SetCameraLookAroundEnabled(bool en)
	{
		cameraLookEn = en;
	}

	bool RenderLayer::GetCameraLookAroundEnabled()
	{
		return cameraLookEn;
	}

	void RenderLayer::OnImguiRender()
	{
	}


}