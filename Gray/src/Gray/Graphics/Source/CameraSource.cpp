#include "grpch.h"
#include "CameraSource.h"
namespace Gray
{
	CameraSource::CameraSource(Camera* camera) : camera(camera)
	{
	}
	const glm::vec3& CameraSource::GetPos()
	{
		return camera->GetPos();
	}
	const glm::vec3& CameraSource::GetDir()
	{
		return camera->GetDir();
	}
}