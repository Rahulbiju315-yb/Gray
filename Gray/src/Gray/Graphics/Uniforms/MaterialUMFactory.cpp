#include "grpch.h"
#include "MaterialUMFactory.h"
#include "Gray/Graphics/Materials.h"
#include "Gray/Graphics/Renderable.h"

namespace Gray
{
    MaterialUM CreateMaterialUM(MaterialUMType type)
    {
        switch (type)
        {
            case MaterialUMType::SimpleMaterialUM :
            {
                static F_MaterialSetter setter = [](const Shader& shader, Renderable* renderable)
                {
                    const Material& material = renderable->GetMaterial();
                    shader.SetUniform("material.diffuse", 0);
                    shader.SetUniform("material.specular", 1);
                    shader.SetUniform("material.emission", 2);

                    material.GetDiffuse()->Bind(0);
                    material.GetSpecular()->Bind(1);
                    material.GetEmission()->Bind(2);

                    shader.SetUniform("material.shininess", material.GetShininess());
                };

                MaterialUM matUM;
                matUM.SetSetterFunction(setter);

                return matUM;
            }

            default:
            {
                static MaterialUM empty;
                return empty;
            }
        }
    }
}