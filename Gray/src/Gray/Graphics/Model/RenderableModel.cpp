#include "grpch.h"
#include "RenderableModel.h"
#include "ModelMaterialUM.h"
#include "Gray/Graphics/Uniforms/TransformUMFactory.h"

namespace Gray
{
	RenderableModel::RenderableModel(std::shared_ptr<Model> model) : model(model)
	{
		isRenderEnabled = true;
		SetMaterialUM(GetModelMaterialUM());
		SetTransformUM(CreateTransformUM(TransformUMType::SimpleTransformUM));

		shader = std::make_shared<Shader>("res/shaders/shader.shader"); // TODO MOVE THIS CODE OUT !!
	}

	inline Transform& RenderableModel::GetTransform()
	{
		return transform;
	}

	void RenderableModel::OnUpdate(float dt) const
	{
		tUM.SetUniformFor(*shader, transform);
		for (auto& mesh : *model)
		{
			auto& rData = mesh.GetRenderData();
			matUM.SetUniformFor(*shader, &mesh.GetMaterial());

			renderer.Draw(*(rData.va), *(rData.ib), *shader);
		}
	}

}