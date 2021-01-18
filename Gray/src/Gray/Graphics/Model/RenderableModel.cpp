 #include "grpch.h"
#include "RenderableModel.h"
#include "Gray/Graphics/ResourceManager.h"

#include "Gray/Graphics/Uniforms/TransformUMFactory.h"
#include "Gray/Graphics/Uniforms/MaterialUMFactory.h"

namespace Gray
{
	uint boundMaterialID;

	RenderableModel::RenderableModel(): validUniforms(false), setter(nullptr), n_instances(0)
	{
		isRenderEnabled = true;

		SetMaterialUM(CreateMaterialUM(MaterialUMType::SimpleMaterialUM));
		SetTransformUM(CreateTransformUM(TransformUMType::SimpleTransformUM));
	}

	void RenderableModel::LoadModel(std::string path, bool flipTexture, bool loadShader)
	{
		model = GetModel(path, flipTexture);
		
		if (loadShader && shader->GetID() == 0)
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
			renderer.Draw(*(rData.va), *(rData.ib), *shader, n_instances);
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

	void RenderableModel::SetOffsets(std::vector<float> offsets)
	{
		NoCopy<VertexBuffer> vb;
		vb->LoadBufferData(&(offsets[0]), sizeof(float) * offsets.size());

		BufferLayout layout;
		layout.Push<float>(3);
		for (Mesh& mesh : model)
		{
			mesh.renderData.va->SetAttribPointers(*vb, layout);
			uint lastAttrib = mesh.renderData.va->GetAttribCount() - 1;
			
			mesh.renderData.va->Bind();
			glVertexAttribDivisor(lastAttrib, 1);
		}
		offsetsBuffer = std::move(vb);

		n_instances = (uint)(offsets.size() / 3);
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