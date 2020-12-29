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

		void LoadTestCube(bool loadShader=true);
		void LoadModel(std::string path, bool loadShader = true);
		void LoadModel(std::shared_ptr<Shader> shader, const RenderData& renderData);
		void LoadModel(float* vertices, uint n_vert, uint* indices, uint n_ind, const BufferLayout& bl,
			bool loadShader = true);

		void AddMesh(const RenderData& renderData);
		Mesh* AddMesh();

		inline virtual Transform& GetTransform();
		virtual void OnUpdate(float dt) override;
		
		std::vector<Mesh>::iterator begin();
		std::vector<Mesh>::iterator end();

		void InvalidateUniforms();
		void SetUniformSetter(UniformSetter setter);

	private:
		Model model;
		Transform transform;
		UniformSetter setter;
		bool validUniforms;

		void SetUniforms();
	};
}