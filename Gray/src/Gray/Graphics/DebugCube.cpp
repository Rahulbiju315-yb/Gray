#include "grpch.h"

#include "DebugCube.h"
#include "Platform/Opengl/test/Util.h"
#include "Uniforms/MaterialUMFactory.h"
#include "Uniforms/TransformUMFactory.h"

namespace Gray
{

	DebugCube::DebugCube()
	{
		isRenderEnabled = true;

		Util::sampleCube(renderData.vb, renderData.ib, renderData.va, this->shader, true);
		transform.SetPos(glm::vec3(0.0f));

		SetMaterialUM(CreateMaterialUM(MaterialUMType::SimpleMaterialUM));
		SetTransformUM(CreateTransformUM(TransformUMType::SimpleTransformUM));
	}

	DebugCube::DebugCube(std::shared_ptr<Shader> shader, RenderData data)
	{
		if (!shader)
		{
			GRAY_CORE_WARN("No shader specified for debugcube constructor");
		}

		this->shader = shader;
		this->renderData = data;

		SetMaterialUM(CreateMaterialUM(MaterialUMType::SimpleMaterialUM));
		SetTransformUM(CreateTransformUM(TransformUMType::SimpleTransformUM));
	}

	void DebugCube::OnUpdate(float dt) const
	{
		tUM.SetUniformFor(*shader, transform);
		matUM.SetUniformFor(*shader, &material);

		renderer.Draw(*(renderData.va), *(renderData.ib), *shader);
	}

	void DebugCube::OnImguiRender() const
	{
	}

	Material& DebugCube::GetMaterial()
	{
		return material;
	}

	void DebugCube::SetRenderData(const RenderData& data)
	{
		this->renderData = renderData;
	}

	const RenderData& DebugCube::GetRenderData() const
	{
		return renderData;
	}

	Transform& DebugCube::GetTransform()
	{
		return transform;
	}

	
}