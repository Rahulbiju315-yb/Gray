#include "grpch.h"

#include "WindowsInput.h"

#include "GLFW/glfw3.h"

namespace Gray
{
    Input* Input::input = nullptr;

    bool WindowsInput::IsKeyPressedImpl(int keyCode)
    {
        GLFWwindow* window = (GLFWwindow*)(Application::GetApp()->GetProvider());
        int state = glfwGetKey(window, keyCode);

        return (state == GLFW_PRESS) || (state == GLFW_REPEAT);
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int mouseButton)
    {
        GLFWwindow* window = (GLFWwindow*)(Application::GetApp()->GetProvider());
        int state = glfwGetMouseButton(window, mouseButton);

        return (state == GLFW_PRESS);
    }

    std::pair<float, float> WindowsInput::GetMousePosImpl()
    {
        GLFWwindow* window = (GLFWwindow*)(Application::GetApp()->GetProvider());

        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return {x, y};
    }

    float WindowsInput::GetMouseXImpl()
    {
		GLFWwindow* window = (GLFWwindow*)(Application::GetApp()->GetProvider());
        
        auto [x, y] = GetMousePosImpl();
        return x;
    }

	float WindowsInput::GetMouseYImpl()
    {
        GLFWwindow* window = (GLFWwindow*)(Application::GetApp()->GetProvider());

        auto [x, y] = GetMousePosImpl();
        return y;
    }
}