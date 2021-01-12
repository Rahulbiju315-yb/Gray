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

                if (material)
                {
                    shader.SetUniform(diff, 0);
                    shader.SetUniform(spec, 1);
                    shader.SetUniform(emm, 2);
                    shader.SetUniform(shine, material->GetShininess());


                    Texture* diffuse = material->GetDiffuse();
                    Texture* specular = material->GetSpecular();
                    Texture* emissive = material->GetEmission();

                    if (diffuse)
                        diffuse->Bind(0);

                    if (specular)
                        specular->Bind(1);

                    if (emissive)
                        emissive->Bind(2);
                }
            }

        };

        MaterialUM matUM;
        matUM.SetSetterFunction(setter);

        return matUM;
    }

	/*MaterialUM ModelMaterialUM()
    {
        static F_MaterialSetter fms = [](const Shader& shader, const Material* material)
        {
            if (material)
            {
                static std::string diff = "material.diffuse";
                static std::string spec = "material.specular";
                static std::string emm = "material.emission";
                static std::string shine = "material.shininess";

                shader.SetUniform(diff, 0);
                shader.SetUniform(spec, 1);
                shader.SetUniform(shine, material->GetShininess());


                material->GetDiffuse()->Bind(0);
                material->GetSpecular()->Bind(1);
            }
        };

        static MaterialUM modelMatUM;
        modelMatUM.SetSetterFunction(fms);
        return modelMatUM;
    }*/
}