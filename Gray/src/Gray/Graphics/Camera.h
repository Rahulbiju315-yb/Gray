#pragma once

#include "Gray/Events/Input.h"
#include "Gray/Events/KeyCodes.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Perspective.h"

namespace Gray
{
	const glm::mat4 UNIT_MAT4 = glm::mat4(1.0f);
	const glm::vec3 Y_AXIS = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 X_AXIS = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 Z_AXIS = glm::vec3(0.0f, 0.0f, 1.0f);

	class Camera
	{
	public:
		Camera(glm::vec3 pos = glm::vec3(0.0f), glm::vec2 dir = glm::vec2(90.0f,
			0.0f), Perspective perspective=defaultPersepective);

		void SetPos(glm::vec3 pos);
		void SetPos(float x, float y, float z);
		const glm::vec3& GetPos() const;

		void SetYawPitch(glm::vec2 yawPitch);
		const glm::vec2& GetYawPitch() const;
		const glm::vec3& GetDir() const;

		const glm::mat4& GetProjection() const;
		const glm::mat4& GetView() const;

		void SetPerspective(const Perspective& perspective);
		void Move(float dt, float speed=1.0f);
		void UpdateLook(float sensitivity=0.05f);

		void OnImguiRender();

	private:
		glm::mat4 proj;
		glm::mat4 view;

		glm::vec3 pos;
		glm::vec3 dir;
		glm::vec2 yawPitch;

		void UpdateView();
	};
}