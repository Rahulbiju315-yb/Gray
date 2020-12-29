#pragma once

#include "glm/glm.hpp"

namespace Gray
{
	class Transform
	{
	public:
		Transform();
		Transform(Transform&& tr) = default;

		const glm::mat4& GetModelMatrix() const;

		void SetPos(glm::vec3 pos);
		const glm::vec3& GetPos() const;

		void SetScale(glm::vec3 scale);
		const glm::vec3& GetScale() const;

		void SetYawPitch(float yaw, float pitch);
		std::tuple<float, float> GetYawPtich() const;

		const glm::vec3& GetDir() const;
	protected:
		glm::mat4 model;
		glm::vec3 pos, scale;

		glm::vec2 yawPitch;
		glm::vec3 dir;

		static const glm::mat4 UNIT_MAT4;

		static const glm::vec3 Y_AXIS;
		static const glm::vec3 X_AXIS;
		static const glm::vec3 Z_AXIS;
	};
}