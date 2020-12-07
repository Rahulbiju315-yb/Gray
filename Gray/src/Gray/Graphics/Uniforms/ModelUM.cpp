#include "grpch.h"
#include "ModelUM.h"
#include "Gray/Graphics/Renderable.h"

namespace Gray
{
	ModelUM::ModelUM() :  renderable(nullptr)
	{
		setter = [](const Shader& shader, Renderable* renderable) {};
	}

	void ModelUM::TieWith(Renderable* renderable)
	{
		this->renderable = renderable;
	}

	void ModelUM::SetSetterFunction(F_ModelSetter setter)
	{
		this->setter = setter;
	}

	void ModelUM::SetUniformFor(const Shader& shader) const
	{
		setter(shader, renderable);
	}

}

