#include "grpch.h"
#include "Gizmo.h"

namespace Gray
{
	ImGuizmo::OPERATION Gizmo::operation = ImGuizmo::TRANSLATE;

	bool Gizmo::GizmoRender(glm::mat4& model, const glm::mat4& view, const glm::mat4& proj)
	{
		bool manipulated = ImGuizmo::Manipulate(&(view[0][0]), &(proj[0][0]),
			operation, ImGuizmo::WORLD, &(model[0][0]), nullptr, nullptr, nullptr, nullptr);

		return manipulated;
	}

	void Gizmo::SetOps(ImGuizmo::OPERATION ops)
	{
		operation = ops;
	}
}