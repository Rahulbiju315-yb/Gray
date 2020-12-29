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

		transform.SetPos(glm::vec3(0.0f));

		SetMaterialUM(CreateMaterialUM(MaterialUMType::SimpleMaterialUM));
		SetTransformUM(CreateTransformUM(TransformUMType::SimpleTransformUM));
	}

	void DebugCube::LoadSampleRD()
	{
		Util::sampleCube(renderData.vb, renderData.ib, renderData.va, this->shader, true);
	}

	void DebugCube::LoadRD(std::shared_ptr<Shader> shader, const RenderData& data)
	{
		this->shader = shader;
		this->renderData = data;
	}

	void DebugCube::OnUpdate(float dt)
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