#include "grpch.h"
#include "ModelUMFactory.h"
#include "Gray/Graphics/Renderable.h"

namespace Gray
{
	ModelUM CreateModelUM(ModelUMType type)
	{
		switch (type)
		{
			case ModelUMType::SimpleModelUM:
			{
				static F_ModelSetter function = [](const Shader& shader, Renderable* renderable) // CAUTION :: Check for validity
				{
					if (renderable)
					{
						static std::string mod = "model";
						static std::string invMod = "invModel";

						const glm::mat4& model = renderable->GetModel()->GetModelMatrix();
						
						shader.SetUniform(mod, model);
						shader.SetUniform(invMod, glm::inverse(model));
					}
				};

				static ModelUM mUM;  // CAUTION :: Check for validity
				mUM.SetSetterFunction(function);
				return mUM;
			}

			default:
			{
				static ModelUM empty;
				return empty;
			}
		}
	}

}
