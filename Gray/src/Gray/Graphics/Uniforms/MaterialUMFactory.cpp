#include "grpch.h"
#include "MaterialUMFactory.h"
#include "Gray/Graphics/Materials.h"
#include "Gray/Graphics/Renderable.h"

namespace Gray
{
    MaterialUM SimpleMaterialUM();
    //MaterialUM ModelMaterialUM();

    MaterialUM CreateMaterialUM(MaterialUMType type)
    {
        switch (type)
        {
            case MaterialUMType::SimpleMaterialUM :
            {
                return SimpleMaterialUM();
            }

            case MaterialUMType::ModelMaterialUM :
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
		static F_MaterialSetter setter = [](const Shader& shader, const Material* material)
        {
            if (material)
            {
                static std::string diff = "material.diffuse";
                static std::string spec = "material.specular";
                static std::string emm = "material.emission";
                static std::string shine = "material.shininess";


                shader.SetUniform(diff, 1);
                shader.SetUniform(spec, 2);
                shader.SetUniform(emm, 3);
                shader.SetUniform(shine, material->GetShininess());

                const Texture* diffuse = material->GetDiffuse();
                const Texture* specular = material->GetSpecular();
                const Texture* emissive = material->GetEmission();

                if (diffuse)
                    diffuse->Bind(1);
                else
                    Defaults::BlankTex()->Bind(1);

                if (specular)
                    specular->Bind(2);
                else
                    Defaults::BlankTex()->Bind(2);

                if (emissive)
                    emissive->Bind(3);
                else 
                    Defaults::BlankTex()->Bind(3);
                
            }
            else
            {
                GRAY_CORE_WARN("Null Material");
            }

        };

        MaterialUM matUM;
        matUM.SetSetterFunction(setter);

        return matUM;
    }
}