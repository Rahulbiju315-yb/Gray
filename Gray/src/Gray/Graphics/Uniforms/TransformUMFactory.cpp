#include "grpch.h"
#include "TransformUMFactory.h"
#include "Gray/Graphics/Renderable.h"

namespace Gray
{
	TransformUM CreateTransformUM(TransformUMType type)
	{
		switch (type)
		{
			case TransformUMType::SimpleTransformUM:
			{
				static F_ModelSetter function = [](const Shader& shader, const Transform& transform) // CAUTION :: Check for validity
				{
					static std::string mod = "model";
					static std::string invMod = "invModel";

					const glm::mat4& model = transform.GetModelMatrix();
						
					shader.SetUniform(mod, model);
					shader.SetUniform(invMod, glm::inverse(model));
				};

				static TransformUM mUM;  // CAUTION :: Check for validity
				mUM.SetSetterFunction(function);
				return mUM;
			}

			default:
			{
				static TransformUM empty;
				return empty;
			}
		}
	}

}
