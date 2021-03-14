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

		void Render(const Shader& shader);

		void SetInstanceOffsets(std::vector<float> offsets);

	private:
		Transform transform;
		Model model;
		NoCopy<VertexBuffer> offsetsBuffer;
		uint n_instances;
		
		void SetTransformUniforms(const Shader& shader);
		void SetMaterialUniforms(const Material& material, const Shader& shader);
		void GroupMeshesByMaterial();
	};
}