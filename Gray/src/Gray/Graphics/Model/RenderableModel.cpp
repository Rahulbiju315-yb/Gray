#include "grpch.h"
#include "RenderableModel.h"
#include "ModelMesh.h"
#include "Platform/Opengl/Renderer.h"

namespace Gray
{
	bool GroupByMaterialComparator(const ModelMesh& m1, const ModelMesh& m2);

	uint boundMaterialID;
	RenderableModel::RenderableModel(): n_instances(0)
	{
		shader->LoadProgram("res/shaders/shader.shader");
	}

	void RenderableModel::SetModel(const Model& m)
	{
		model = m;
	}

	Transform& RenderableModel::GetTransform() { return transform; }

	void RenderableModel::Render()
	{
		assert(model.meshes.size() != 0);
		SetTransformUniforms();
		for (auto& mesh : model)
		{
			SetMaterialUniforms(mesh.material);
			boundMaterialID = mesh.material.GetID();

			auto& rData = mesh.renderData;
			assert((rData.va)->GetID() != 0);
			assert((rData.vb)->GetID() != 0);
			assert((rData.ib)->GetID() != 0);
			assert((shader->GetID()) != 0);
			Draw(*(rData.va), *(rData.ib), *shader, n_instances);
		}
	}

	
	void RenderableModel::SetInstanceOffsets(std::vector<float> offsets)
	{
		NoCopy<VertexBuffer> vb;
		vb->LoadBufferData(&(offsets[0]), sizeof(float) * offsets.size());

		BufferLayout layout;
		layout.Push<float>(3);
		for (ModelMesh& mesh : model)
		{
			mesh.renderData.va->SetAttribPointers(*vb, layout);
			uint lastAttrib = mesh.renderData.va->GetAttribCount() - 1;
			
			mesh.renderData.va->Bind();
			glVertexAttribDivisor(lastAttrib, 1);
		}
		offsetsBuffer = std::move(vb);

		n_instances = (uint)(offsets.size() / 3);
	}

	Shared<Shader> RenderableModel::GetShader(){ return shader; }
	void RenderableModel::SetShader(Shared<Shader> shader) { this->shader = shader; }

	void RenderableModel::GroupMeshesByMaterial()
	{
		std::sort(model.meshes.begin(), model.meshes.end(), &GroupByMaterialComparator);
	}
	
	void RenderableModel::SetTransformUniforms()
	{
		static std::string mod = "model";
		static std::string invMod = "invModel";

		const glm::mat4& model = transform.GetModelMatrix();
		
		shader->SetUniform(mod, model);
		shader->SetUniform(invMod, glm::inverse(model));
	}

	void RenderableModel::SetMaterialUniforms(const Material& material)
	{
		static std::string diff = "material.diffuse";
        static std::string spec = "material.specular";
        static std::string emm = "material.emission";
        static std::string shine = "material.shininess";

        shader->SetUniform(diff, 1);
        shader->SetUniform(spec, 2);
        shader->SetUniform(emm, 3);
        shader->SetUniform(shine, material.GetShininess());

        WeakRef<Texture> diffuse = material.GetDiffuse();
        WeakRef<Texture> specular = material.GetSpecular();
        WeakRef<Texture> emissive = material.GetEmission();

		diffuse->Bind(1);
		specular->Bind(2);
		emissive->Bind(3);
	}

	bool GroupByMaterialComparator(const ModelMesh& m1, const ModelMesh& m2)
	{
		return m1.material.GetID() < m2.material.GetID();
	}
}