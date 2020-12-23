#pragma once

#include "Gray/Graphics/Uniforms/MaterialUM.h"
#include "Gray/Graphics/Materials.h"

namespace Gray
{
    static MaterialUM GetModelMaterialUM()
    {
        static MaterialUM modelMatUM;
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
                    (material->GetDiffuseMaps()[0]).Bind(0);

                if (material->GetSpecularMaps().size() != 0)
                    (material->GetSpecularMaps()[0]).Bind(1);
            }
        };
        modelMatUM.SetSetterFunction(fms);
        return modelMatUM;
    }
}