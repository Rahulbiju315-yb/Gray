#pragma once

#include "glm/glm.hpp"
namespace Gray
{
	class EditorCamera
    {
    public:
        EditorCamera();

        void Rotate(glm::vec2 dyawPitch);
        void Pan(float sensitivity=0.05f);
        void Zoom(float alpha);

        const glm::mat4 GetView() const;
        const glm::mat4& GetProjection() const;

        glm::vec3 focusPoint;

    private:
        void RecalculateView();

        glm::mat4 view;
        glm::mat4 projection;

        glm::vec3 viewPosition;
        glm::vec2 yawPitch;
    };
}