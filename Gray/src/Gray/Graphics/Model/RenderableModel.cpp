 #include "grpch.h"
#include "RenderableModel.h"

#include "Gray/Graphics/Uniforms/TransformUMFactory.h"
#include "Gray/Graphics/Uniforms/MaterialUMFactory.h"

namespace Gray
{
	uint boundMaterialID;

	RenderableModel::RenderableModel(): validUniforms(false), setter(nullptr)
	{
		isRenderEnabled = true;

		SetMaterialUM(CreateMaterialUM(MaterialUMType::SimpleMaterialUM));
		SetTransformUM(CreateTransformUM(TransformUMType::SimpleTransformUM));
	}

	void RenderableModel::LoadModel(std::string path, bool flipTexture, bool loadShader)
	{
		std::string dir = path.substr(0, path.find_last_of('/'));
		std::string name = path.substr(path.find_last_of('/') + 1, path.size());

		model.LoadModel(dir, name, flipTexture);
		
		if (loadShader)
		{
			shader = Shared<Shader>();
			shader -> LoadProgram("res/shaders/shader.shader");
		}

		SortByMaterial();
	}

	void RenderableModel::LoadModel(float* vertices, uint n_vert, uint* indices, uint n_ind, const BufferLayout& bl,
		bool loadShader)
	{
		model.meshes.push_back(Mesh());
		model.meshes.back().SetupMesh(vertices, n_vert, indices, n_ind, bl);

		if (loadShader)
		{
			shader = Shared<Shader>();
			shader -> LoadProgram("res/shaders/shader.shader");
		}
	}

	Mesh* RenderableModel::AddMesh()
	{
		model.meshes.push_back(Mesh());
		return &model.meshes.back();
	}

	void RenderableModel::OnUpdate(float dt)
	{
		tUM.SetUniformFor(*shader, transform);
		for (auto& mesh : model)
		{
			if (boundMaterialID != mesh.material.GetID())
			{
				matUM.SetUniformFor(*shader, &mesh.material);
				boundMaterialID = mesh.material.GetID();
			}

			auto& rData = mesh.renderData;
			renderer.Draw(*(rData.va), *(rData.ib), *shader);
		}
	}

	std::vector<Mesh>::iterator RenderableModel::begin()
	{
		return model.begin();
	}

	std::vector<Mesh>::iterator RenderableModel::end()
	{
		return model.end();
	}

	void RenderableModel::SetUniformSetter(UniformSetter setter)
	{
		this->setter = setter;
	}

	
	bool GroupByMaterialComparator(const Mesh& m1, const Mesh& m2)
	{
		return m1.material.GetID() < m2.material.GetID();
	}

	void RenderableModel::SortByMaterial()
	{
		std::sort(model.meshes.begin(), model.meshes.end(), &GroupByMaterialComparator);
	}

}