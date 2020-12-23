#pragma once

#include "Gray/Graphics/Transform.h"
#include "Platform/Opengl/Shader.h"

namespace Gray
{

	class Renderable;

	typedef void (*F_ModelSetter)(const Shader&, const Transform&);

	enum class TransformUMType
	{
		SimpleTransformUM
	};

	class TransformUM
	{
	public:
		TransformUM();

		void SetSetterFunction(F_ModelSetter setter);
		virtual void SetUniformFor(const Shader& shader, const Transform& transform) const;

	protected:
		Renderable* renderable;
		F_ModelSetter setter;
	};
}