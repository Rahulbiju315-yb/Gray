#include "grpch.h"
#include "CameraController.h"
#include "Gray/Math/Math.h"
#include "Gray/Events/Input.h"
#include "Gray/Events/EventListener.h"
#include "Gray/Events/MouseEvent.h"
#include "Gray/Window/Window.h"
#include "Gray/Math/Constants.h"

namespace Gray
{
	class ZoomListener : public EventListener
	{
	public:

		ZoomListener()
			: dscroll(0.0f)
		{
			Window::GetWindow()->AddListener(this);
		}

		void OnEvent(Event& e, EventType type) override
		{
			if (type == EventType::MouseScrolled)
			{
				MouseScrolledEvent& mse = (MouseScrolledEvent&)e;

				float yoffset = mse.GetYOffset();
				dscroll += yoffset;
			}
		}

		float dscroll;
	};

	void CameraController::Control(EditorCamera& ec, float sensitivity)
	{ 
		static ZoomListener zl;

		glm::vec2 dyawPitch = { Input::GetMouseDX() * sensitivity,
								-Input::GetMouseDY() * sensitivity };

		if(Input::IsMouseButtonPressed(MouseCodes::MouseMiddle))
			ec.Rotate(dyawPitch);

		if(zl.dscroll)
			ec.Zoom(zl.dscroll * 0.1f);

		zl.dscroll = 0;
	}

	void CameraController::Control(SceneCamera& sc, float dt, float sensitivity, float speed)
	{
		glm::vec2 dyawPitch = { Input::GetMouseDX() * sensitivity,
		                       -Input::GetMouseDY() * sensitivity };

		glm::vec2 newYawPitch = sc.GetYawPitch() + dyawPitch;
		sc.LookAt(newYawPitch);

		glm::vec3 z = glm::normalize(sc.GetDir());
		glm::vec3 x = glm::normalize(glm::cross(Y_AXIS, z));

		glm::vec3 moveDir = { 0, 0, 0 };

		if (Input::IsKeyPressed(TO_INT(KeyCodes::Key_W)))
			moveDir += z;

		if (Input::IsKeyPressed(TO_INT(KeyCodes::Key_A)))
			moveDir += x;

		if (Input::IsKeyPressed(TO_INT(KeyCodes::Key_S)))
			moveDir -= z;

		if (Input::IsKeyPressed(TO_INT(KeyCodes::Key_D)))
			moveDir -= x;
		
		if(moveDir != glm::vec3{0, 0, 0})
			moveDir = glm::normalize(moveDir);

		sc.MoveAlong(moveDir, dt, speed);
	}


}