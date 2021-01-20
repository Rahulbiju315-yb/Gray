#include "grpch.h"

#include "Camera.h"
#include "Scene.h"
#include "cmath"
#include "imgui.h"

namespace Gray
{
	Camera::Camera(glm::vec3 pos, glm::vec2 yawPitch, Perspective perspective)
		: pos(pos),
		view(glm::mat4(1.0f))

	{
		SetYawPitch(yawPitch);
		proj = glm::perspective(perspective.fov, perspective.aspectRatio, perspective.zLimNear, perspective.zLimFar);
	}

	void Camera::UpdateLook(float sensitivity)
	{
		float dyaw = Input::GetMouseDX() * sensitivity;
		float dpitch =  -Input::GetMouseDY() * sensitivity;

		this->yawPitch.x += dyaw;
		this->yawPitch.y += dpitch;

		if (this->yawPitch.y > 89.0f)
			this->yawPitch.y = 89.0f;

		else if (this->yawPitch.y < -89.0f)
			this->yawPitch.y = -89.0f; 

		SetYawPitch(yawPitch);
		UpdateView();
	}

	void Camera::OnImguiRender()
	{
		glm::vec3 pos = GetPos();
		glm::vec2 yawPitch = GetYawPitch();

		std::string cPos = "Pos : " + std::to_string(pos.x) + ", " + std::to_string(pos.y);
		std::string cDir = "Dir (yaw, pitch) : " + std::to_string(yawPitch.x) + ", " + std::to_string(yawPitch.y);

		ImGui::Text(cPos.c_str());
		ImGui::Text(cDir.c_str());
	}

	void Camera::SetPerspective(const Perspective& perspective)
	{
		proj = glm::perspective(perspective.fov, perspective.fov, perspective.zLimNear, perspective.zLimFar);
	}

	void Camera::Move(float dt, float speed)
	{
		float k = dt * speed;

		glm::vec3 z_ = k * glm::normalize(glm::vec3(dir.x, dir.y, dir.z));
		glm::vec3 x_ = k * glm::normalize(glm::vec3(-dir.z, 0, dir.x));

		if (Gray::Input::IsKeyPressed((int)(Gray::KeyCodes::Key_W)))
		{
			SetPos(pos + z_);
			UpdateView();
		}

		if (Gray::Input::IsKeyPressed((int)(Gray::KeyCodes::Key_A)))
		{
			SetPos(pos - x_);
			UpdateView();
		}

		else if (Gray::Input::IsKeyPressed((int)(Gray::KeyCodes::Key_S)))
		{
			SetPos(pos - z_);
			UpdateView();
		}

		else if (Gray::Input::IsKeyPressed((int)(Gray::KeyCodes::Key_D)))
		{
			SetPos(pos + x_);
			UpdateView();
		}
	}

	void Camera::UpdateView()
	{
		view = glm::lookAt(pos, pos + dir, Y_AXIS);
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

	void Camera::SetYawPitch(glm::vec2 yawPitch)
	{
		this->yawPitch = yawPitch;

		//yaw : yawPitch.x
		//pitch : yawPitch.y
		float yaw = glm::radians(yawPitch.x);
		float pitch = glm::radians(yawPitch.y);

		dir = glm::vec3(cos(pitch) * cos(yaw), sin(pitch), cos(pitch) * sin(yaw));
	}

	const glm::vec3& Camera::GetPos()
	{
		return pos;
	}
	
	const glm::vec2& Camera::GetYawPitch()
	{
		return yawPitch;
	}

	const glm::vec3& Camera::GetDir()
	{
		return dir;
	}

	const glm::mat4& Camera::GetProjection()
	{
		return proj;
	}

	const glm::mat4& Camera::GetView()
	{
		return view;
	}
}