#pragma once
#include "UniformManager.h"

namespace Gray
{
	class Renderable;
	typedef void(*F_MaterialSetter)(const Shader&, Renderable*);


	enum class MaterialUMType
	{
		SimpleMaterialUM
	};

	class MaterialUM : public UniformManager
	{
	public:
		MaterialUM();

		virtual void SetUniformFor(const Shader& shader) const override;
		virtual void TieWith(Renderable* renderable);
		void SetSetterFunction(F_MaterialSetter setter);

	protected:
		Renderable* renderable;
		F_MaterialSetter setter;
	};

}