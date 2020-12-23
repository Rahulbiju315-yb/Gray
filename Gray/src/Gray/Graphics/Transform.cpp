#include "grpch.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Transform.h"

namespace Gray
{
	const glm::mat4 Transform::UNIT_MAT4 = glm::mat4(1.0f);

	const glm::vec3 Transform::Y_AXIS = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 Transform::X_AXIS = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 Transform::Z_AXIS = glm::vec3(0.0f, 0.0f, 1.0f);


	Transform::Transform() : scale(glm::vec3(1.0f))
	{
		SetPos(glm::vec3(0, 0, 0));
		SetYawPitch(0, 0);
	}

	void Transform::SetPos(glm::vec3 pos)
	{
		//model - glm::translate(model, (pos - this->pos));
		model = glm::scale(glm::translate(UNIT_MAT4, pos), scale);
		this->pos = pos;
	}

	const glm::vec3& Transform::GetPos() const
	{
		return pos;
	}

	void Transform::SetScale(glm::vec3 scale)
	{
		model = glm::scale(model, scale);
		this->scale = scale;
	}

	const glm::vec3& Transform::GetScale() const
	{
		return scale;
	}

	void Transform::SetYawPitch(float yaw, float pitch)
	{
		model = glm::rotate(model, glm::radians(yaw), Y_AXIS);
		model = glm::rotate(model, glm::radians(pitch), X_AXIS);

		dir = glm::vec3(glm::cos(pitch) * glm::cos(yaw),
						glm::sin(pitch),
						glm::cos(pitch) * glm::sin(yaw));

		yawPitch = glm::vec2(yaw, pitch);
	}

	std::tuple<float, float> Transform::GetYawPtich() const
	{
		return std::tuple<float, float>(yawPitch.x, yawPitch.y);
	}

	const glm::vec3& Transform::GetDir() const
	{
		return dir;
	}



	const glm::mat4& Transform::GetModelMatrix() const
	{
		return model;
	}
}
