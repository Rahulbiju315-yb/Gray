#include "grpch.h"
#include "RenderableModel.h"

#include "Gray/Graphics/Uniforms/TransformUMFactory.h"
#include "Gray/Graphics/Uniforms/MaterialUMFactory.h"

#include "Platform/Opengl/test/Util.h"

namespace Gray
{
	RenderableModel::RenderableModel(): validUniforms(false), setter(nullptr)
	{
		isRenderEnabled = true;

		SetMaterialUM(CreateMaterialUM(MaterialUMType::SimpleMaterialUM));
		SetTransformUM(CreateTransformUM(TransformUMType::SimpleTransformUM));
	}

	void RenderableModel::LoadTestCube(bool loadShader)
	{
		model.meshes.push_back(Mesh());

		RenderData renderData;
		Util::sampleCube(renderData.vb, renderData.ib, renderData.va, this->shader, loadShader);
		model.meshes.back().SetupMesh(renderData);
	}

	void RenderableModel::LoadModel(std::string path, bool loadShader)
	{
		std::string dir = path.substr(0, path.find_last_of('/'));
		std::string name = path.substr(path.find_last_of('/') + 1, path.size());

		
		model.LoadModel(dir, name);
		
		if(loadShader)
			shader = std::make_shared<Shader>("res/shaders/shader.shader");
	}

	void RenderableModel::LoadModel(std::shared_ptr<Shader> shader, const RenderData& renderData)
	{
		this->shader = shader;
		model.meshes.push_back(Mesh());
		(model.meshes.back()).SetupMesh(renderData);
	}

	void RenderableModel::LoadModel(float* vertices, uint n_vert, uint* indices, uint n_ind, const BufferLayout& bl,
		bool loadShader)
	{
		model.meshes.push_back(Mesh());
		model.meshes.back().SetupMesh(vertices, n_vert, indices, n_ind, bl);

		if(loadShader)
			shader = std::make_shared<Shader>("res/shaders/shader.shader");
	}
 
	void RenderableModel::AddMesh(const RenderData& renderData)
	{
		model.meshes.push_back(Mesh());
		auto mesh = &(model.meshes.back());
		mesh->SetupMesh(renderData);
		//model.materials.push_back(std::shared_ptr());
	}

	Mesh* RenderableModel::AddMesh()
	{
		model.meshes.push_back(Mesh());
		return &model.meshes.back();
	}

	inline Transform& RenderableModel::GetTransform()
	{
		return transform;
	}

	void RenderableModel::OnUpdate(float dt)
	{
		SetUniforms();
		for (auto& mesh : model)
		{
			auto& rData = mesh.GetRenderData();
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

	void RenderableModel::InvalidateUniforms()
	{
		validUniforms = false;
	}

	void RenderableModel::SetUniformSetter(UniformSetter setter)
	{
		this->setter = setter;
	}

	void RenderableModel::SetUniforms()
	{
		if (!validUniforms)
		{
			if (!setter) // Default to the following uniform settings
			{
				tUM.SetUniformFor(*shader, transform);
				auto& materials = model.GetMaterials();

				if (model.GetMaterials().size() == 1)
				{
					GRAY_WARN("No materials provided for rendering the given model");
					matUM.SetUniformFor(*shader, &materials[0]);
				}

				else if (model.GetMaterials().size() != 0)
				{
					auto& material = materials[1];
					matUM.SetUniformFor(*shader, &material);
				}

				if (materials.size() > 1)
					GRAY_WARN("number of materials for this model is greater than 1. Only first material will be used");

				validUniforms = true;
			}
			else
			{
				setter(*shader, *this);
			}
		}
	}
}