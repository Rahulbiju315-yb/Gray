#include "grpch.h"
#include "Camera.h"

namespace Gray
{
	Camera::Camera(glm::vec3 pos, glm::vec2 dir)
	{
		this->pos = pos;
		this->dir = dir;

		aspectRatio = 4.0f / 3.0f;
		zLim = glm::vec2(0.1f, 100.0f);
		SetZoom(45.0f);
	}

	Camera::~Camera()
	{
	}

	void Camera::SetAspectRatio(float aspectRatio)
	{
		this->aspectRatio = aspectRatio;
	}

	void Camera::SetZLimits(glm::vec2 zLim)
	{
		this->zLim = zLim;
	}

	void Camera::SetPos(glm::vec3 pos)
	{
		this->pos = pos;
	}

	void Camera::SetPos(float x, float y, float z)
	{
		this->pos.x = x;
		this->pos.y = y;
		this->pos.z = z;
	}

	void Camera::SetDir(glm::vec2 dir)
	{
		this->dir = dir;
	}

	void Camera::SetDir(float yaw, float pitch)
	{
		this->dir.x = yaw;
		this->dir.y = pitch;
	}

	const glm::vec3& Camera::GetPos()
	{
		return pos;
	}

	const glm::vec2& Camera::GetDir()
	{
		return dir;
	}

	float Camera::GetAspectRatio()
	{
		return aspectRatio;
	}

	const glm::vec2& Camera::GetZLimits()
	{
		return zLim;
	}

	void Camera::SetZoom(float alpha)
	{
		this->alpha = alpha;
		proj = glm::perspective(glm::radians(alpha), aspectRatio, zLim.x, zLim.y);

	}

	const glm::mat4& Camera::GetProjection()
	{
		return proj;
	}

	const glm::mat4& Camera::GetView()
	{
		view = glm::rotate(UNIT_MAT4, glm::radians((float)(dir.x)), Y_AXIS);
		view = glm::rotate(view, glm::radians((float)(dir.y)), X_AXIS);
		view = glm::translate(view, -pos);

		return view;
	}
}