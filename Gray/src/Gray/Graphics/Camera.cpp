#include "grpch.h"

#include "Camera.h"
#include "Scene.h"

#include "cmath"
namespace Gray
{
	Camera::Camera(Scene* scene, glm::vec3 pos, glm::vec2 yawPitch) : 
	pos(pos), yawPitch(yawPitch), zLim(glm::vec2(0.1f, 100.0f)), view(glm::mat4(1.0f)), 
	aspectRatio(4.0f / 3.0f), alpha(45.0f), speed(1.0f), sensitivity(1 / 20.f),
	mX(-1), mY(-1), camMoveEn(true), camLookAroundEn(true), scene(scene)

	{
		SetZoom(alpha);
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

	void Camera::UpdatePos(float dx, float dy, float dz)
	{
		this->pos.x += dx;
		this->pos.y += dy;
		this->pos.z += dz;
	}

	void Camera::SetDir(glm::vec2 yawPitch)
	{
		this->yawPitch = yawPitch;
	}

	void Camera::SetDir(float yaw, float pitch)
	{
		this->yawPitch.x = yaw;
		this->yawPitch.y = pitch;
	}

	void Camera::UpdateDir(float dyaw, float dpitch)
	{
		this->yawPitch.x += dyaw;
		this->yawPitch.y += dpitch;

		if (this->yawPitch.y > 89.0f)
			this->yawPitch.y = 89.0f;

		else if (this->yawPitch.y < -89.0f)
			this->yawPitch.y = -89.0f; 

		float yaw = glm::radians(yawPitch.x);
		float pitch = glm::radians(yawPitch.y);

		dir = glm::vec3(cos(pitch)* cos(yaw), sin(pitch), cos(pitch) * sin(yaw));
	}

	float Camera::GetSpeed()
	{
		return speed;
	}

	float Camera::GetSensitivity()
	{
		return sensitivity;
	}

	bool Camera::GetMoveEnabled()
	{
		return camMoveEn;
	}

	bool Camera::GetLookAroundEnabled()
	{
		return camLookAroundEn;
	}

	void Camera::SetSpeed(float speed)
	{
		this->speed = speed;
	}

	void Camera::SetSensitivity(float sensitivity)
	{
		this->sensitivity = sensitivity;
	}

	void Camera::SetMoveEnabled(bool en)
	{
		camMoveEn = en;
	}

	void Camera::SetLookAroundEnabled(bool en)
	{
		camLookAroundEn = en;
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

		float yaw = glm::radians(yawPitch.x);
		float pitch = glm::radians(yawPitch.y);

		view = glm::lookAt(pos, pos + dir, Y_AXIS);

		return view;
	}

	void Camera::UpdateLook()
	{
		if (camMoveEn)
		{
			float mXn = Input::GetMouseX();
			float mYn = Input::GetMouseY();

			if (mX == -1)
			{
				mX = mXn;
				mY = mYn;
			}

			else
			{
				UpdateDir((mXn - mX) * sensitivity, (-mYn + mY) * sensitivity);
			}

			mX = mXn;
			mY = mYn;
		}
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

	void Camera::SetViewUniformsFor(Shader* shader)
	{
		shader->SetUniform("view", GetView());
	}

	void Camera::OnUpdate(float dt)
	{
		Move(dt);
	}

	void Camera::Move(float dt)
	{
		if (camMoveEn)
		{
			const auto& view = scene->GetCamera()->GetView();
			auto unique_shaders = scene->GetShaderSet();

			for (auto shader : unique_shaders)
				shader->SetUniform("viewPos", pos);

			const glm::vec2& yawPitch = GetYawPitch();
			const glm::vec3& pos = GetPos();

			float yaw = glm::radians(yawPitch.x);
			float pitch = glm::radians(yawPitch.y);

			float k = dt * speed;

			glm::vec3 z_ = k * glm::normalize(glm::vec3(dir.x, 0, dir.z));
			glm::vec3 x_ = k * glm::normalize(glm::vec3(-dir.z, 0, dir.x));

			if (Gray::Input::IsKeyPressed((int)(Gray::KeyCodes::Key_W)))
			{
				SetPos(pos + z_);
			}

			if (Gray::Input::IsKeyPressed((int)(Gray::KeyCodes::Key_A)))
			{
				SetPos(pos - x_);
			}

			else if (Gray::Input::IsKeyPressed((int)(Gray::KeyCodes::Key_S)))
			{
				SetPos(pos - z_);
			}

			else if (Gray::Input::IsKeyPressed((int)(Gray::KeyCodes::Key_D)))
			{
				SetPos(pos + x_);
			}
		}
		
	}
}