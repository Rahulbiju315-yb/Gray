#pragma once

#include "Platform/Opengl/Renderer.h"
#include "Platform/Opengl/Shader.h"
#include "Platform/Opengl/RenderData.h"

#include "imgui.h"
#include "Materials.h"

#include "Uniforms/MaterialUM.h"
#include "Uniforms/ModelUM.h"

#include "Model/Model.h"

//Inconsistent use of references and pointers.
//To be fixed after determining the better usage.

//Is it okay for PointLightSource and renderable to be in the same file??
//Better layout possible?? 

namespace Gray
{
	class Renderable
	{
	public:
		Renderable(const Renderable&) = delete;
		Renderable& operator=(const Renderable&) = delete;

		Renderable();
		Renderable(RenderData renderData);

		virtual void OnUpdate(float dt) const = 0;
		virtual void SetUniforms() const = 0;
		virtual void OnImguiRender() const { }

		void SetRenderEnabled(bool en);
		bool GetRenderEnabled() const;

		std::shared_ptr<Shader> GetShader();
		void SetShader(std::shared_ptr<Shader> shader);

		void SetMaterial(Material material);
		Material* GetMaterial();
		
		void SetMaterialUM(MaterialUM materialUM);
		void SetModelUM(ModelUM modelUM);

		Model* GetModel();

		void SetRenderData(RenderData renderData);
		RenderData GetRenderData() const;

		static const Renderer* GetRenderer();

	protected:
		static const Renderer renderer;

		Material material;
		Model model;
		RenderData renderData;
		std::shared_ptr<Shader> shader;

		bool isRenderEnabled;

		void SetModelUniforms() const;
		void SetMaterialUniforms() const;

		const ModelUM& GetModelUM() const;
		const MaterialUM& GetMaterialUM() const;
		
	private:
		ModelUM modelUM;
		MaterialUM materialUM;

	};
	typedef std::shared_ptr<Renderable> SharedRenderable;

}