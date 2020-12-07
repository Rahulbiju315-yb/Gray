#include "grpch.h"

#include "DebugCube.h"
#include "Platform/Opengl/test/Util.h"
#include "Uniforms/MaterialUMFactory.h"
#include "Uniforms/ModelUMFactory.h"

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

		modelUM = CreateModelUM(ModelUMType::SimpleModelUM);
		materialUM = CreateMaterialUM(MaterialUMType::SimpleMaterialUM);

	}

	void DebugCube::SetUniforms() const
	{
		SetModelUniforms();
		SetMaterialUniforms();
	}

	void DebugCube::OnUpdate(float dt) const
	{
		renderer.Draw(*va, *ib, *shader);
	}

	void DebugCube::OnImguiRender() const
	{
	}

	void DebugCube::free()
	{
		va = nullptr;
		vb = nullptr;
		ib = nullptr;
	}
}