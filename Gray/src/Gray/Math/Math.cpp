#include "grpch.h"
#include "Math.h"
#include "Constants.h"

namespace Gray
{
	

	void RotateToVectorFrom(glm::vec3 v1, glm::vec3 v2, glm::mat4& mat)
	{
		glm::vec3 cross = glm::cross(v1, v2);
		float alpha = glm::acos(glm::dot(glm::normalize(v1), glm::normalize(v2)));

		mat = glm::rotate(UNIT_MAT4, alpha, cross);	
	}

	glm::mat4 RotationYPR(glm::vec3 yawPitchRoll)
	{
		glm::mat4 mat = UNIT_MAT4;

		float yaw = glm::radians(yawPitchRoll.x);
		float pitch = glm::radians(yawPitchRoll.y);
		float roll = glm::radians(yawPitchRoll.z);

		float cosYaw = glm::cos(yaw);
		float sinYaw = glm::sin(yaw);

		float cosPitch = glm::cos(-pitch);
		float sinPitch = glm::sin(-pitch);
		 
		float cosRoll = glm::cos(roll);
		float sinRoll = glm::sin(roll);

		mat[0][0] = cosYaw * cosPitch;
		mat[0][1] = cosRoll * sinPitch + cosPitch * sinRoll * sinYaw;
		mat[0][2] = sinRoll * sinPitch - cosRoll * cosPitch * sinYaw;

		mat[1][0] = -cosYaw * sinPitch;
		mat[1][1] = cosRoll * cosPitch - sinRoll * sinYaw * sinPitch;
		mat[1][2] = cosPitch * sinRoll + cosRoll * sinYaw * sinPitch;

		mat[2][0] = sinYaw;
		mat[2][1] = -cosYaw * sinRoll;
		mat[2][2] = cosRoll * cosYaw;

		return mat;
	}

	glm::vec3 YawPitchToXYZ(glm::vec2 yawPitch)
	{
		float yaw = glm::radians(yawPitch.x);
		float pitch = glm::radians(yawPitch.y);

		glm::vec3 dir = glm::vec3(cos(pitch) * cos(yaw), sin(pitch), cos(pitch) * sin(yaw));

		return dir;
	}
}