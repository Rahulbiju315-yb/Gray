#include "grpch.h"
#include "SceneCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Gray/Math/Math.h"
#include "Perspective.h"
#include "Gray/Math/Constants.h"

namespace Gray
{
	SceneCamera::SceneCamera()
		: pos({ 0, 0, 0 }),
		  view(UNIT_MAT4),
		  yawPitch({ 90, 0 })
	{
		dir = YawPitchToXYZ(yawPitch);
		defaultPersepective.GetProjectionMatrix(projection);
	}

	void SceneCamera::MoveAlong(glm::vec3 moveDir, float dt, float speed)
	{
		pos = pos + (moveDir * dt * speed);
		view = glm::lookAt(pos, pos + dir, Y_AXIS);
	}

	void SceneCamera::LookAt(glm::vec2 yawPitch)
	{
		this->yawPitch = yawPitch;
		dir = YawPitchToXYZ(yawPitch);
		view = glm::lookAt(pos, pos + dir, Y_AXIS);
	}

	const glm::mat4& SceneCamera::GetView()
	{
		return view;
	}

	const glm::mat4& SceneCamera::GetProjection()
	{
		return projection;
	}

	glm::vec3 SceneCamera::GetPos()
	{
		return pos;
	}

	glm::vec3 SceneCamera::GetDir()
	{
		return dir;
	}

	glm::vec2 SceneCamera::GetYawPitch()
	{
		return yawPitch;
	}

}