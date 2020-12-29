#pragma once

#include "Platform/Opengl/Shader.h"
#include "Gray/Graphics/Materials.h"

namespace Gray
{
	class Renderable;
	typedef void(*F_MaterialSetter)(const Shader&, const Material*);


	enum class MaterialUMType
	{
		SimpleMaterialUM,
		ModelMaterialUM
	};

	class MaterialUM
	{
	public:
		MaterialUM();

		virtual void SetUniformFor(const Shader& shader, const Material* material) const;
		void SetSetterFunction(F_MaterialSetter setter);

	protected:
		F_MaterialSetter setter;
	};

}