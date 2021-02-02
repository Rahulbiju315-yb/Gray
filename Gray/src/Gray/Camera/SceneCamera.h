#pragma once

#include "glm/glm.hpp"
namespace Gray
{
	class SceneCamera
	{
	public:
		SceneCamera();

		void MoveAlong(glm::vec3 moveDir, float dt, float speed=1.0f);
        void LookAt(glm::vec2 yawPitch);
		
		const glm::mat4& GetView();
		const glm::mat4& GetProjection();

		glm::vec3 GetPos();
		glm::vec3 GetDir();
		glm::vec2 GetYawPitch();

	private:
		glm::mat4 view;
		glm::mat4 projection;

		glm::vec3 pos;
		glm::vec3 dir;
		glm::vec2 yawPitch;
	};
}