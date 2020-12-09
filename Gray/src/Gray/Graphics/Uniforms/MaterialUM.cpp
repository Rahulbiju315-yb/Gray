#include "grpch.h"
#include "Gray/Graphics/Renderable.h"
#include "MaterialUM.h"

namespace Gray
{
	MaterialUM::MaterialUM() : renderable(nullptr)
	{
		setter = [](const Shader& shader, Renderable* renderable) {};
	}

	void MaterialUM::SetUniformFor(const Shader& shader) const
	{
		if(renderable)
			setter(shader, renderable);
	}

	void MaterialUM::TieWith(Renderable* renderable)
	{
		this->renderable = renderable;
	}

	void MaterialUM::SetSetterFunction(F_MaterialSetter setter)
	{
		this->setter = setter;
	}
}