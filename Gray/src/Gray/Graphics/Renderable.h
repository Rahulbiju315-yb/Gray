#pragma once

#include "Platform/Opengl/Renderer.h"
#include "Platform/Opengl/Opengl.h"

#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"

#include "Materials.h"
#include "LightColor.h"

//Inconsistent use of references and pointers.
//To be fixed after determining the better usage.

//Is it okay for PointLightSource and renderable to be in the same file??
//Better layout possible?? 

namespace Gray
{
	class Renderable;
	class Debug;

	class Debug
	{
	public:
		void StandardLightingDebug(Renderable* r);

	};

	class Renderable
	{
	public:
		virtual void OnUpdate(float dt) { }
		virtual void SetUniforms() {}
		virtual void OnImguiRender() { }

		void SetRenderEnabled(bool en);
		bool GetRenderEnabled();

		void SetName(std::string name);
		const std::string& GetName();

		std::shared_ptr<Shader> GetShader();
		void SetShader(std::shared_ptr<Shader> shader);

		const glm::vec3& GetPos();
		void SetPos(glm::vec3 pos);

		const glm::vec3& GetDir();
		void SetYawPitch(glm::vec2 yawPitch);

		static const Renderer* GetRenderer();

		void SetMaterial(Material material);
		Material* GetMaterial();

	protected:
		std::string name;

		static const glm::mat4 UNIT_MAT4;
		static const Renderer renderer;

		Material material;

		std::unique_ptr<VertexBuffer> vb;
		std::unique_ptr<IndexBuffer> ib;
		std::unique_ptr<VertexArray> va;
		std::shared_ptr<Shader> shader;

		Debug debug;

		glm::vec3 scale;
		glm::vec3 pos;
		glm::vec2 yawPitch;
		glm::vec2 dir;

		bool isRenderEnabled;

		void SetModelUniforms();
		void SetMaterialUniforms();

	};
	typedef std::shared_ptr<Renderable> SharedRenderable;

}