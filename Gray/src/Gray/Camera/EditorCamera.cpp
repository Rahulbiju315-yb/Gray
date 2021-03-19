#include "grpch.h"
#include "EditorCamera.h"
#include "Gray/Events/Input.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

#include "Gray/Math/Math.h"

#include "Perspective.h"
#include "Gray/Math/Constants.h"

namespace Gray
{
	EditorCamera::EditorCamera()
		: viewPosition({ 2, 0, 0 }),
		  focusPoint({ 0, 0, 0 }),
		  view(UNIT_MAT4),
		  invView(UNIT_MAT4),
		  yawPitch({ 0, 0 })
	{
		Perspective p = defaultPersepective;
		p.zLimFar = 500.0f;
		p.GetProjectionMatrix(projection);
		RecalculateView();
	}

	void EditorCamera::Rotate(glm::vec2 dyawPitch)
	{
		yawPitch += dyawPitch;
		RecalculateView();
	}

	void EditorCamera::Pan(glm::vec2 dpos2d)
	{
		glm::vec3 dpos3dW = invView * glm::vec4{ dpos2d, 0 , 0 };
		focusPoint += dpos3dW;
		viewPosition += dpos3dW;
		RecalculateView();
	}

	void EditorCamera::Zoom(float alpha)
	{
		glm::vec3 deltaViewPos = (focusPoint - viewPosition) * alpha;
		viewPosition += deltaViewPos;
		RecalculateView();
	}

	const glm::mat4& EditorCamera::GetView() const
	{
		return view;
	}

	const glm::mat4& EditorCamera::GetProjection() const
	{
		return projection;
	}

	const glm::vec3& EditorCamera::GetPos() const
	{
		return viewPosition;
	}

	const glm::vec3& EditorCamera::GetFocusPoint() const
	{
		return focusPoint;
	}

	void EditorCamera::SetFocusPoint(const glm::vec3& fp)
	{
		focusPoint = fp;
		RecalculateView();
	}

	void EditorCamera::RecalculateView()
	{
		glm::vec3 tr = { 0, 0, glm::length((focusPoint - viewPosition)) };
		view = glm::lookAt(viewPosition, focusPoint, Y_AXIS);
		view[3] += glm::vec4{ tr, 0 };
		view = glm::eulerAngleZXY(0.0f, glm::radians(-yawPitch.y), glm::radians(yawPitch.x)) * view;
		view[3] += glm::vec4{ -tr, 0 };
		invView = glm::inverse(view);
	}
}