#include "grpch.h"

#include "DebugCube.h"
#include "Platform/Opengl/test/Util.h"

namespace Gray
{

	DebugCube::DebugCube(bool initShader, std::shared_ptr<Shader> shader, glm::vec3 pos)
	{
		isRenderEnabled = true;

		Util::sampleCube(vb, ib, va, this->shader, initShader);

		SetPos(pos);

		if(!initShader)
		{
			if (shader == nullptr)
				GRAY_CORE_ERROR("No default shader specified and initShader set to null!!");

			this->shader = shader;
		}

		scale = glm::vec3(1.0f);
	}


	void DebugCube::SetUniforms()
	{
		SetModelUniforms();
		SetMaterialUniforms();
	}

	void DebugCube::OnUpdate(float dt)
	{
		renderer.Draw(*va, *ib, *shader);
	}

	void DebugCube::OnImguiRender()
	{
		debug.StandardLightingDebug(this);
	}
}