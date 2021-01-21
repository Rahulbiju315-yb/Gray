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

		void SetPath(const std::string& path);
		bool TryToLoadModel();

		Transform& GetTransform();
		virtual void Render();

		void SetTransformUniforms();
		void SetMaterialUniforms(const Material& material);

		void SetInstanceOffsets(std::vector<float> offsets);

		Shared<Shader> GetShader();
		void SetShader(Shared<Shader> shader);
	private:
		Model model;
		Transform transform;
		Shared<Shader> shader;
		NoCopy<VertexBuffer> offsetsBuffer;
		uint n_instances;

		void SortByMaterial();
	};
}