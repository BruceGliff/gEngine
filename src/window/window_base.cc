#include "debug/debug.h"

#include "window_base.h"

#include "process/global.h"
#include "actor/actor.h"
#include "actor/components/camera.h"


#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <initializer_list>


// class will be global variable for GLFW to access
Resources::WindowSizeProperty WindowProperty;


Resources::WindowSizeProperty& Resources::WindowSizeProperty::operator=(std::initializer_list<int>&& list)
{
    if (list.size() != 2)
    {
        width = 1600;
        height = 900;
        gWARNING(std::string{ "Wrong initializer list size! window will be with size: " } + std::to_string(width) + std::string{ "x" } + std::to_string(height));
        return *this;
    }

    width = *list.begin();
    height = *(list.begin() + 1);

    return *this;
}

Resources::glWindow::glWindow(int width, int height, std::string const & win_name) : name{win_name}
{
    WindowProperty = { width, height };
    pWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    if (!pWindow)
    {
        gERROR("window creating failed!");
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    /* Set up my own function */
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    glfwSetCursorPosCallback(pWindow, mouse_callback);
    glfwSetScrollCallback(pWindow, scroll_callback);

    glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

Resources::glWindow::operator bool() const noexcept
{
    return glfwWindowShouldClose(pWindow);
}

Resources::WindowSizeProperty const & Resources::glWindow::GetWindowSize() const noexcept
{
    return WindowProperty;
}

Resources::WindowSizeProperty& Resources::glWindow::GetWindowSize() noexcept
{
    return WindowProperty;
}

void Resources::glWindow::Draw() const noexcept
{
    /* Swap front and back buffers */
    glfwSwapBuffers(pWindow);

    /* Poll for and process events */
    glfwPollEvents();
}

bool Resources::glWindow::ProcessInput() const noexcept
{
    static float deltaTime = 0.0f;	// Time between current frame and last frame
    static float lastFrame = 0.0f; // Time of last frame

    float currentFrame = static_cast<float>(glfwGetTime()); // cast from double to float
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    const float cameraSpeed = 20.5f * deltaTime;

    auto& player = GLOBAL::GetPlayer();
    auto& player_pos = player.GetPosition();
    Component::camera & cam = *player.GetComponentByName<Component::camera>("camera");
    auto& cameraFront = cam.GetFront();
    auto& cameraUp = cam.GetUp();

    if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
        player_pos += cameraSpeed * cameraFront;
    if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
        player_pos -= cameraSpeed * cameraFront;
    if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
        player_pos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
        player_pos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    // close windows if it should be
    return glfwWindowShouldClose(pWindow);
}

void Resources::glWindow::glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    WindowProperty.width = width;
    WindowProperty.height = height;
    glViewport(0, 0, WindowProperty.width, WindowProperty.height);
}
 

// TODO check this with Process input!
void Resources::glWindow::glfwKeyCallback(GLFWwindow* window, int key, int scanmode, int action, int mode)
{
    // Close window due to escape
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        // Set up window property what is has to be closed
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void Resources::glWindow::mouse_callback(GLFWwindow* window, double xpos_d, double ypos_d)
{
    // PARAMS of MOUSE or camera
    //                      ^
    float xpos = static_cast<float>(xpos_d);
    float ypos = static_cast<float>(ypos_d);
    static bool firstMouse = true;
    static float lastX = 1600.f / 2.f;
    static float lastY = 900.f / 2.f;
    static float yaw = -90.0f;	
    static float pitch = 0.0f;


    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.4f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    auto& cameraFront = GLOBAL::GetPlayer().GetComponentByName<Component::camera>("camera")->GetFront();
    cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Resources::glWindow::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    auto& fov = static_cast<Component::camera*>(GLOBAL::GetPlayer().GetComponent("camera"))->GetFOV();
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}