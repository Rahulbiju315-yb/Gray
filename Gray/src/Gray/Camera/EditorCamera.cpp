#include "grpch.h"
#include "EditorCamera.h"
#include "Gray/Events/Input.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

#include "Gray/Math/Math.h"
#include "Gray/Events/MouseCodes.h"

#include "Perspective.h"
#include "Gray/Math/Constants.h"

namespace Gray
{
	EditorCamera::EditorCamera()
		: viewPosition({ 2, 0, 0 }),
		  focusPoint({ 0, 0, 0 }),
		  view(UNIT_MAT4),
		  yawPitch({ 90, 0 })
	{
		defaultPersepective.GetProjectionMatrix(projection);
	}

	void EditorCamera::Rotate(glm::vec2 dyawPitch)
	{
		yawPitch += dyawPitch;
		RecalculateView();
	}

	void EditorCamera::Pan(float sensitivity)
	{

	}

	void EditorCamera::Zoom(float alpha)
	{
		glm::vec3 deltaViewPos = (focusPoint - viewPosition) * alpha;
		viewPosition += deltaViewPos;
		RecalculateView();
	}

	const glm::mat4 EditorCamera::GetView()
	{
		return view;
	}

	const glm::mat4& EditorCamera::GetProjection()
	{
		return projection;
	}

	void EditorCamera::RecalculateView()
	{
		glm::vec3 tr = { 0, 0, -glm::length((focusPoint - viewPosition)) };
		view = glm::lookAt(viewPosition, focusPoint, Y_AXIS);
		view = glm::translate(view, -tr);
		view = glm::eulerAngleZXY(0.0f, glm::radians(-yawPitch.y), glm::radians(yawPitch.x));
		view[3] = glm::vec4(+tr, 1);
	}
}