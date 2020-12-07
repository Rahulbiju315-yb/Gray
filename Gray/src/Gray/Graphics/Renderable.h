#pragma once

#include "Platform/Opengl/Renderer.h"
#include "Platform/Opengl/Opengl.h"

#include "imgui.h"
#include "Materials.h"
#include "Uniforms/MaterialUM.h"
#include "Uniforms/ModelUM.h"

//Inconsistent use of references and pointers.
//To be fixed after determining the better usage.

//Is it okay for PointLightSource and renderable to be in the same file??
//Better layout possible?? 

namespace Gray
{
	class Renderable
	{
	public:
		virtual void OnUpdate(float dt) const = 0;
		virtual void SetUniforms() const = 0;
		virtual void OnImguiRender() const { }

		void SetRenderEnabled(bool en);
		bool GetRenderEnabled() const;

		void SetName(std::string name);
		const std::string& GetName() const;

		std::shared_ptr<Shader> GetShader();
		void SetShader(std::shared_ptr<Shader> shader);

		const glm::vec3& GetPos() const;
		void SetPos(glm::vec3 pos);

		const glm::vec3& GetDir() const;
		void SetYawPitch(glm::vec2 yawPitch);

		static const Renderer* GetRenderer();

		void SetMaterial(Material material);
		const Material& GetMaterial() const;

		void SetMaterialUM(MaterialUM materialUM);
		void SetModelUM(ModelUM modelUM);

		const glm::mat4& GetModel() const;

	protected:
		std::string name;

		static const glm::mat4 UNIT_MAT4;
		static const Renderer renderer;

		Material material;
		MaterialUM materialUM;

		std::shared_ptr<VertexBuffer> vb;
		std::shared_ptr<IndexBuffer> ib;
		std::shared_ptr<VertexArray> va;
		std::shared_ptr<Shader> shader;

		glm::mat4 model;
		ModelUM modelUM;

		glm::vec3 scale;
		glm::vec3 pos;
		glm::vec2 yawPitch;
		glm::vec3 dir;

		bool isRenderEnabled;

		void SetModelUniforms() const;
		void SetMaterialUniforms() const;

	};
	typedef std::shared_ptr<Renderable> SharedRenderable;

}