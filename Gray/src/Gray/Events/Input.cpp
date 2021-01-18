#include "grpch.h"
#include "Input.h"
#include "GLFW/glfw3.h"
#include "Gray/Window/Window.h"

namespace Gray
{
	bool Input::IsKeyPressed(int keyCode)
    {
        GLFWwindow* window = Window::GetWindow()->GetGLFWwindow();
        int state = glfwGetKey(window, keyCode);

        return (state == GLFW_PRESS) || (state == GLFW_REPEAT);
    }

    bool Input::IsMouseButtonPressed(int mouseButton)
    {
        GLFWwindow* window = Window::GetWindow()->GetGLFWwindow();
        int state = glfwGetMouseButton(window, mouseButton);

        return (state == GLFW_PRESS);
    }

    std::pair<float, float> Input::GetMousePos()
    {
        GLFWwindow* window = Window::GetWindow()->GetGLFWwindow();

        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return {(float)x, (float)y};
    }

    float Input::GetMouseX()
    {
		GLFWwindow* window = Window::GetWindow()->GetGLFWwindow();
        
        auto [x, y] = GetMousePos();
        return x;
    }

	float Input::GetMouseY()
    {
        GLFWwindow* window = Window::GetWindow()->GetGLFWwindow();

        auto [x, y] = GetMousePos();
        return y;
    }
}