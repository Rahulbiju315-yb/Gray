#pragma once

#include "Renderable.h"
#include "Gray/Events/Input.h"
#include "Gray/Events/KeyCodes.h"

namespace Gray
{
	class Scene;
	class Camera
	{
	public:
		Camera(Scene* scene, glm::vec3 pos = glm::vec3(0.0f), glm::vec2 dir = glm::vec2(90.0f,
			0.0f));
		~Camera();

		void SetAspectRatio(float aspectRatio);
		void SetZLimits(glm::vec2 zLim);

		void SetPos(glm::vec3 pos);
		void SetPos(float x, float y, float z);
		void UpdatePos(float dx, float dy, float dz);

		void SetDir(glm::vec2 dir);
		void SetDir(float yaw, float pitch);
		void UpdateDir(float dyaw, float dpitch);
		
		float GetSpeed();
		float GetSensitivity();
		bool GetMoveEnabled();
		bool GetLookAroundEnabled();

		void SetSpeed(float speed);
		void SetSensitivity(float sensitivity);
		void SetMoveEnabled(bool en);
		void SetLookAroundEnabled(bool en);
	
		const glm::vec3& GetPos();
		const glm::vec2& GetYawPitch();
		const glm::vec3& GetDir();

		float GetAspectRatio();
		const glm::vec2& GetZLimits();

		void SetZoom(float alpha);
		const glm::mat4& GetProjection();
		const glm::mat4& GetView();

		void OnUpdate(float dt);
		void Move(float dt);
		void UpdateLook();

		void OnImguiRender();

		void SetViewUniformsFor(Shader* shader);
	private:

		const glm::mat4 UNIT_MAT4 = glm::mat4(1.0f);
		const glm::vec3 Y_AXIS = glm::vec3(0.0f, 1.0f, 0.0f);
		const glm::vec3 X_AXIS = glm::vec3(1.0f, 0.0f, 0.0f);
		const glm::vec3 Z_AXIS = glm::vec3(0.0f, 0.0f, 1.0f);

		glm::vec3 pos;
		glm::vec3 dir;
		glm::vec2 yawPitch;
		glm::vec2 zLim;
		glm::mat4 proj;
		glm::mat4 view;

		float aspectRatio;
		float alpha;
		float speed;
		float sensitivity;
		float mX, mY;

		bool camMoveEn;
		bool camLookAroundEn;
		Scene* scene;
	};
}