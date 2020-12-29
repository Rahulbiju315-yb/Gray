#include "grpch.h"
#include "MaterialUMFactory.h"
#include "Gray/Graphics/Materials.h"
#include "Gray/Graphics/Renderable.h"

namespace Gray
{
    MaterialUM SimpleMaterialUM();
    MaterialUM ModelMaterialUM();

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
                return ModelMaterialUM();
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

                shader.SetUniform(diff, 0);
                shader.SetUniform(spec, 1);
                shader.SetUniform(emm, 2);
                shader.SetUniform(shine, material->GetShininess());

                if (material->GetDiffuseMaps().size() != 0)
                    (material->GetDiffuseMaps()[0])->Bind(0);

                if (material->GetSpecularMaps().size() != 0)
                    (material->GetSpecularMaps()[0])->Bind(1);

                if (material->GetEmissionMaps().size() != 0)
                    (material->GetEmissionMaps()[0])->Bind(2);
            }

        };

        MaterialUM matUM;
        matUM.SetSetterFunction(setter);

        return matUM;
    }

	MaterialUM ModelMaterialUM()
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

                if (material->GetDiffuseMaps().size() != 0)
                    (material->GetDiffuseMaps()[0])->Bind(0);

                if (material->GetSpecularMaps().size() != 0)
                    (material->GetSpecularMaps()[0])->Bind(1);
            }
        };

        static MaterialUM modelMatUM;
        modelMatUM.SetSetterFunction(fms);
        return modelMatUM;
    }
}