#pragma once
#include "UniformManager.h"

namespace Gray
{

	class Renderable;

	typedef void (*F_ModelSetter)(const Shader&, Renderable*);

	enum class ModelUMType
	{
		SimpleModelUM
	};

	class ModelUM : public UniformManager
	{
	public:
		ModelUM();

		void TieWith(Renderable* renderable);
		void SetSetterFunction(F_ModelSetter setter);
		
		virtual void SetUniformFor(const Shader& shader) const override;
	protected:
		Renderable* renderable;
		F_ModelSetter setter;
	};
}