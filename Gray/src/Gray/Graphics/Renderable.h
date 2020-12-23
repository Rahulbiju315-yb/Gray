#pragma once

#include "RenderListItem.h"

#include "Platform/Opengl/Renderer.h"
#include "Platform/Opengl/Shader.h"
#include "Platform/Opengl/RenderData.h"

#include "imgui.h"
#include "Materials.h"

#include "Uniforms/MaterialUM.h"
#include "Uniforms/TransformUM.h"

#include "Transform.h"

//Inconsistent use of references and pointers.
//To be fixed after determining the better usage.

//Is it okay for PointLightSource and renderable to be in the same file??
//Better layout possible?? 

namespace Gray
{
	class Renderable : public RenderListItem
	{
	public:
		Renderable();

		virtual void OnUpdate(float dt) const override = 0;
		virtual void OnImguiRender() const { }

		void SetRenderEnabled(bool en);
		bool GetRenderEnabled() const;

		std::shared_ptr<Shader> GetShader();
		void SetShader(std::shared_ptr<Shader> shader);

		static const Renderer* GetRenderer();

		void SetTransformUM(TransformUM tUM);
		void SetMaterialUM(MaterialUM matUM);

	protected:
		static const Renderer renderer;
		bool isRenderEnabled;

		std::shared_ptr<Shader> shader;
		TransformUM tUM;
		MaterialUM matUM;
	};

}