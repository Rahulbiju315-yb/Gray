#pragma once

#include "Renderable.h"
#include "Gray/Layers/RenderLayer.h"

#include "Gray/Events/Input.h"

namespace Gray
{
	class Camera : public Renderable
	{
	public:
		Camera(glm::vec3 pos = glm::vec3(0.0f), glm::vec2 dir = glm::vec2(glm::radians(0.0f)));
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

		void SetSpeed(float speed);
		void SetSensitivity(float sensitivity);

		const glm::vec3& GetPos();
		const glm::vec2& GetDir();
		float GetAspectRatio();
		const glm::vec2& GetZLimits();

		void SetZoom(float alpha);
		const glm::mat4& GetProjection();
		const glm::mat4& GetView();

		void OnUpdate(float dt) override;
		void Move(float dt);
		void UpdateLook();

		void OnImguiRender() override;
	private:

		

		const glm::mat4 UNIT_MAT4 = glm::mat4(1.0f);
		const glm::vec3 Y_AXIS = glm::vec3(0.0f, 1.0f, 0.0f);
		const glm::vec3 X_AXIS = glm::vec3(1.0f, 0.0f, 0.0f);
		const glm::vec3 Z_AXIS = glm::vec3(0.0f, 0.0f, 1.0f);

		glm::vec3 pos;
		glm::vec2 dir;
		glm::vec2 zLim;
		glm::mat4 proj;
		glm::mat4 view;

		float alpha;
		float aspectRatio;

		float mX, mY;
		float speed;
		float sensitivity;

		bool hasPosChanged;
	};
}