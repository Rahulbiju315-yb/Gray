#include "grpch.h"
#include "MaterialUMFactory.h"
#include "Gray/Graphics/Materials.h"
#include "Gray/Graphics/Renderable.h"

namespace Gray
{
    MaterialUM SimpleMaterialUM();

    MaterialUM CreateMaterialUM(MaterialUMType type)
    {
        switch (type)
        {
            case MaterialUMType::SimpleMaterialUM :
            {
                return SimpleMaterialUM();
            }

            default:
            {
                static MaterialUM empty;
                return empty;
            }
        }
    }

    MaterialUM SimpleMaterialUM()
    {
		static F_MaterialSetter setter = [](const Shader& shader, Renderable* renderable)
                {
                    static std::string diff = "material.diffuse";
                    static std::string spec = "material.specular";
                    static std::string emm = "material.emission";
                    static std::string shine = "material.shininess";

                    Material* material = renderable->GetMaterial();
                    shader.SetUniform(diff, 0);
                    shader.SetUniform(spec, 1);
                    shader.SetUniform(emm, 2);
                    shader.SetUniform(shine, material->GetShininess());
            
                    material->GetDiffuse()->Bind(0);
                    material->GetSpecular()->Bind(1);
                    material->GetEmission()->Bind(2);

                };

        MaterialUM matUM;
        matUM.SetSetterFunction(setter);

        return matUM;
    }

}