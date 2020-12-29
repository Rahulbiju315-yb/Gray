#pragma once

//Renders cube for debug purposes

#include "Gray/Graphics/Renderable.h"
#include "Gray/Graphics/Transformable.h"

namespace Gray
{
	class DebugCube : public Renderable, public Transformable
	{
	public:
		DebugCube();

		void LoadSampleRD();
		void LoadRD(std::shared_ptr<Shader> shader, const RenderData& data);

		virtual void OnUpdate(float dt) override;
		virtual void OnImguiRender() const override;

		virtual Material& GetMaterial();

		virtual void SetRenderData(const RenderData& renderData);
		virtual const RenderData& GetRenderData() const;

		virtual Transform& GetTransform();
	protected:

		Material material;
		RenderData renderData;
		Transform transform;
	};
}