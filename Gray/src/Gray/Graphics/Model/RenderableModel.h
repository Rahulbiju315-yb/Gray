#pragma once

#include "Model.h"
#include "Gray/Graphics/Transform.h"
#include "Platform/Opengl/Shader.h"

namespace Gray
{

	class RenderableModel
	{
	public:
		RenderableModel();
		RenderableModel(const RenderableModel& model) = delete;
		RenderableModel(RenderableModel&& model) = default;

		void SetModel(const Model& m);

		Transform& GetTransform();
		void Render();

		void SetInstanceOffsets(std::vector<float> offsets);

		Shared<Shader> GetShader();
		void SetShader(Shared<Shader> shader);

	private:
		Transform transform;
		Model model;
		Shared<Shader> shader;
		NoCopy<VertexBuffer> offsetsBuffer;
		uint n_instances;

		
		void SetTransformUniforms();
		void SetMaterialUniforms(const Material& material);
		void GroupMeshesByMaterial();
	};
}