#pragma once

#include "glm/glm.hpp"
namespace Gray
{
	class EditorCamera
    {
    public:
        EditorCamera();

        void Rotate(glm::vec2 dyawPitch);
        void Pan(glm::vec2 dpos);
        void Zoom(float alpha);

        const glm::mat4& GetView() const;
        const glm::mat4& GetProjection() const;
        const glm::vec3& GetPos() const;
        const glm::vec3& GetFocusPoint() const;

        void SetFocusPoint(const glm::vec3& fp);

    private:
        void RecalculateView();

        glm::mat4 view;
        glm::mat4 invView;
        glm::mat4 projection;

        glm::vec3 viewPosition;
        glm::vec3 focusPoint;
        glm::vec2 yawPitch;
    };
}