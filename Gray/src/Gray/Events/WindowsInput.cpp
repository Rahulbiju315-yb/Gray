#include "grpch.h"
#include "WindowsInput.h"
#include "GLFW/glfw3.h"
#include "Gray/Application.h"

bool Gray::WindowsInput::IsKeyPressedImpl(int keyCode)
{
    GLFWwindow* window = (GLFWwindow*)(Application::GetApp()->GetProvider());
    int state = glfwGetKey(window, keyCode);

    return (state == GLFW_PRESS) || (state == GLFW_REPEAT);
}

bool Gray::WindowsInput::IsMouseButtonPressedImpl(int mouseButton)
{
    GLFWwindow* window = (GLFWwindow*)(Application::GetApp()->GetProvider());
    int state = glfwGetMouseButton(window, mouseButton);

    return (state == GLFW_PRESS);
}
