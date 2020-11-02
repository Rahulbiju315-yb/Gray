#pragma once

#include "Platform/Opengl/Renderer.h"
#include "Platform/Opengl/Opengl.h"

#include "imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

//Inconsistent use of references and pointers.
//To be fixed after determining the better usage.
namespace Gray
{
	class Renderable;
	class Debug;

	class Renderable
	{
	public:
		virtual void OnUpdate(float dt) { }
		virtual void OnImguiRender() { }

		void SetRenderEnabled(bool en) { isRenderEnabled = en; }
		bool GetRenderEnabled() { return isRenderEnabled; }

		void SetName(std::string name) { this->name = name; }
		const std::string& GetName() { return name; }

		const glm::mat4& GetModel() { return model; }
		const glm::vec3& GetPos() { return pos; }

		Shader* GetShader() { return shader; }

		void SetPos(glm::vec3 pos) 
		{ 
			this->pos = pos; 
			model = glm::translate(UNIT_MAT4, pos);
			shader->SetUniform("model", model);
		}

		static void SetRenderer(Renderer* renderer)
		{
			Renderable::renderer = renderer;
		}

		static Renderer* GetRenderer() { return renderer;  }


	protected:
		std::string name;

		const glm::mat4 UNIT_MAT4 = glm::mat4(1.0f);

		glm::mat4 model;
		glm::vec3 pos;
	
		static Renderer* renderer;
		VertexBuffer* vb;
		IndexBuffer* ib;
		VertexArray* va;
		Shader* shader;

		Debug* debug;

		bool isRenderEnabled;

	};

	class Debug
	{
	public:
		void StandardLightingDebug(Renderable* r);
	};
}