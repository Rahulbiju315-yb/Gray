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
						const glm::mat4& model = renderable->GetModel();
						shader.SetUniform("model", model);
						shader.SetUniform("invModel", glm::inverse(model));
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
