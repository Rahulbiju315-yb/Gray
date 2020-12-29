#pragma once
#include "Source.h"
#include "Gray/Graphics/Camera.h"
namespace Gray
{
	class CameraSource : public Source
	{
	public:
		CameraSource(Camera* camera);
		virtual const glm::vec3& GetPos() override;
		virtual const glm::vec3& GetDir() override;

		Camera* camera;
	};
}