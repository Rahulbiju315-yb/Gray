#include "grpch.h"

#include "DebugCube.h"
#include "Platform/Opengl/test/Util.h"
#include "Uniforms/MaterialUMFactory.h"
#include "Uniforms/ModelUMFactory.h"

namespace Gray
{

	DebugCube::DebugCube()
	{
		isRenderEnabled = true;

		Util::sampleCube(renderData.vb, renderData.ib, renderData.va, this->shader, true);
		model.SetPos(glm::vec3(0.0f));

	}

	DebugCube::DebugCube(std::shared_ptr<Shader> shader, RenderData data)
	{
		if (!shader)
		{
			GRAY_CORE_WARN("No shader specified for debugcube constructor");
		}

		this->shader = shader;
		this->renderData = data;
	}


	void DebugCube::SetUniforms() const
	{
		SetModelUniforms();
		SetMaterialUniforms();
	}

	void DebugCube::OnUpdate(float dt) const
	{
		renderer.Draw(*(renderData.va), *(renderData.ib), *shader);
	}

	void DebugCube::OnImguiRender() const
	{
	}

}