#pragma once

#include "Gray/Graphics/Transform.h"
#include "Gray/Mesh/Mesh.h"
#include "Platform/Opengl/Shader.h"
#include "Platform/Opengl/Texture.h"
#include "glm/glm.hpp"

namespace Gray
{
	class DebugCube
	{
	public:
		glm::mat4 model;

		DebugCube();
		void Render(const Shader& shader);

	private:
		NoCopyMesh mesh;
	};
}