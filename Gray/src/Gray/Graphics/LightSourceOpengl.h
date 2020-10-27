#pragma once

#include "LightSource.h"
#include "Renderable.h"

#include "Platform/Opengl/Opengl.h"
#include "Platform/Opengl/test/Util.h"

namespace Gray
{
	class GRAY_API LightSourceOpengl : public LightSource, public Renderable
	{
	public:
		LightSourceOpengl(glm::vec4 color = glm::vec4(1.0f));
		~LightSourceOpengl();

		void SetColor(glm::vec4 color) override;
		const glm::vec4& GetColor() override;
		
		void SetPos(glm::vec3 pos) override;
		const glm::vec3& GetPos(glm::vec3 pos) override;

		void OnUpdate(float dt) override;

		Shader* GetShader();

	private:
		glm::vec4 color;
		glm::vec3 pos;

		VertexArray* va;
		VertexBuffer* vb;
		IndexBuffer* ib;
		Shader* shader;

		glm::mat4 model;

	};
}