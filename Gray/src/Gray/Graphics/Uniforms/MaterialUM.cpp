#include "grpch.h"
#include "Gray/Graphics/Renderable.h"
#include "MaterialUM.h"

namespace Gray
{
	MaterialUM::MaterialUM()
	{
		setter = [](const Shader& shader, const Material*) {};
	}

	void MaterialUM::SetUniformFor(const Shader& shader, const Material* material) const
	{
		setter(shader, material);
	}

	void MaterialUM::SetSetterFunction(F_MaterialSetter setter)
	{
		this->setter = setter;
	}
}