#pragma once

#include "glm/glm.hpp"
#include "ImGuizmo/ImGuizmo.h"

namespace Gray
{
	class Gizmo
	{
	public:
		static bool GizmoRender(glm::mat4& model, const glm::mat4& view, const glm::mat4& proj);
		static void SetOps(ImGuizmo::OPERATION ops);

	private:
		static ImGuizmo::OPERATION operation;
	};
	
}