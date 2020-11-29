#include "grpch.h"

#include "WindowsInput.h"

#include "GLFW/glfw3.h"

#include "Gray/Window/Window.h"
namespace Gray
{
    Input* Input::input = nullptr;

    bool WindowsInput::IsKeyPressedImpl(int keyCode)
    {
        GLFWwindow* window = (GLFWwindow*)(Window::GetProvider());
        int state = glfwGetKey(window, keyCode);

        return (state == GLFW_PRESS) || (state == GLFW_REPEAT);
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int mouseButton)
    {
        GLFWwindow* window = (GLFWwindow*)(Window::GetProvider());
        int state = glfwGetMouseButton(window, mouseButton);

        return (state == GLFW_PRESS);
    }

    std::pair<float, float> WindowsInput::GetMousePosImpl()
    {
        GLFWwindow* window = (GLFWwindow*)(Window::GetProvider());

        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return {(float)x, (float)y};
    }

    float WindowsInput::GetMouseXImpl()
    {
		GLFWwindow* window = (GLFWwindow*)(Window::GetProvider());
        
        auto [x, y] = GetMousePosImpl();
        return x;
    }

	float WindowsInput::GetMouseYImpl()
    {
        GLFWwindow* window = (GLFWwindow*)(Window::GetProvider());

        auto [x, y] = GetMousePosImpl();
        return y;
    }
}