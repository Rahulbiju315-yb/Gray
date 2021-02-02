#pragma once
#include "Platform/Opengl/Shader.h"
#include "Gray/Mesh/Mesh.h"
#include "Gray/Graphics/Light/LightingManager.h"
namespace Gray
{
	struct Light
	{
		uint ID;
		Gray::LightType ltype;
	};

	class LightingEditor
	{
	public:
		LightingEditor();

		void DrawEditor();
		const LightingManager& GetLightingManager() const;

	private:
		NoCopy<Shader> pointerShader;
		NoCopyMesh pointerMesh;

		LightingManager lightMan;
		std::vector<Light> lightsIDs;
		std::vector<std::string> names;
	};
}