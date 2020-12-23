#include "grpch.h"
#include "TransformUM.h"

namespace Gray
{
	TransformUM::TransformUM() :  renderable(nullptr)
	{
		setter = [](const Shader& shader, const Transform& transform) {};
	}

	void TransformUM::SetSetterFunction(F_ModelSetter setter)
	{
		this->setter = setter;
	}

	void TransformUM::SetUniformFor(const Shader& shader, const Transform& transform) const
	{
		setter(shader, transform);
	}

}

