#include "grpch.h"

#include "DebugCube.h"
#include "Platform/Opengl/test/Util.h"

namespace Gray
{
	DebugCube::DebugCube(bool initShader, glm::vec3 pos)
	{
		//Add opengl context checking later perhaps??
		Util::sampleObject2(vb, ib, va, shader, true);
		
		//shader->Bind();
		tex = new Texture("res/textures/t4.jpg", GL_RGB, GL_RGB);
		tex->Bind();
		shader->SetUniform("tex1", 0);

		SetPos(glm::vec3(0.0f, 0.0f, 3.0f));
		shader->SetUniform("model", model);

		debug = new Debug();
	}

	DebugCube::~DebugCube()
	{
		delete vb;
		delete va;
		delete ib;
		delete shader;
	}

	void DebugCube::OnUpdate(float dt)
	{
		if (renderer != nullptr)
		{
			renderer->Draw(*va, *ib, *shader);
		}
		else
			GRAY_CORE_ERROR("Renderer not initialised !!!");
	}

	void DebugCube::OnImguiRender()
	{
		debug->StandardLightingDebug(this);
	}
}