#pragma once

#include "Model.h"
#include "Gray/Graphics/Renderable.h"
#include "Gray/Graphics/Transformable.h"

namespace Gray
{
	typedef void (*UniformSetter)(const Shader&, RenderableModel&);

	class RenderableModel : public Renderable, public Transformable
	{
	public:
		RenderableModel();
		RenderableModel(const RenderableModel& model) = delete;
		RenderableModel(RenderableModel&& model) = default;

		void LoadModel(std::string path, bool flipTexture, bool loadShader = true);
		void LoadModel(float* vertices, uint n_vert, uint* indices, uint n_ind, const BufferLayout& bl,
			bool loadShader = true);

		Mesh* AddMesh();

		virtual Transform& GetTransform() override { return transform; }
		virtual void OnUpdate(float dt) override;
		
		std::vector<Mesh>::iterator begin();
		std::vector<Mesh>::iterator end();

		void SetUniformSetter(UniformSetter setter);

	private:
		Model model;
		Transform transform;
		UniformSetter setter;
		bool validUniforms;

		void SortByMaterial();
	};
}