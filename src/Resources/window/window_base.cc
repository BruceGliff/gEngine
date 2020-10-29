#include "window_base.h"

#include "../process/global.h"

#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <exception>

// This is CRUTCH
// TODO make it more common with OOP
namespace global
{
    int g_x = 0;
    int g_y = 0;
}


Resources::glWindows::glWindows() : glWindows(1600, 900, "weed_pepe")
{
}

Resources::glWindows::glWindows(int width, int height, std::string const & win_name) : x(width), y(height), name{win_name}
{
    pWindow = glfwCreateWindow(x, y, name.c_str(), nullptr, nullptr);
    if (!pWindow)
    {
        std::cerr << "ERROR:: window creating failed!" << std::endl;
        throw std::runtime_error{ "EXCEPTION:: window creating failed!" };
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    /* Set up my own function */
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    glfwSetCursorPosCallback(pWindow, mouse_callback);
    glfwSetScrollCallback(pWindow, scroll_callback);
}

Resources::glWindows::operator bool() const noexcept
{
    return glfwWindowShouldClose(pWindow);
}

void Resources::glWindows::Draw() const noexcept
{
    /* Swap front and back buffers */
    glfwSwapBuffers(pWindow);

    /* Poll for and process events */
    glfwPollEvents();
}

bool Resources::glWindows::ProcessInput() const noexcept
{
    static float deltaTime = 0.0f;	// Time between current frame and last frame
    static float lastFrame = 0.0f; // Time of last frame

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    const float cameraSpeed = 2.5f * deltaTime;

    Actor::actor_base& player = GLOBAL::GetPlayer();
    auto& cameraPos = player.cameraPos;
    auto& cameraFront = player.cameraFront;
    auto& cameraUp = player.cameraUp;

    if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    // close windows if it should be
    return glfwWindowShouldClose(pWindow);
}

void Resources::glWindows::glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    global::g_x = width;
    global::g_y = height;
    glViewport(0, 0, global::g_x, global::g_y);
}
 

// TODO check this with Process input!
void Resources::glWindows::glfwKeyCallback(GLFWwindow* window, int key, int scanmode, int action, int mode)
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
void Resources::glWindows::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    // PARAMS of MOUSE or camera
    //                      ^
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
    auto& cameraFront = GLOBAL::GetPlayer().cameraFront;
    cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Resources::glWindows::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    auto& fov = GLOBAL::GetPlayer().fov;
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

Resources::GFLW_Wrap::GFLW_Wrap()
{
    static int number_of_copies = 0;
    if (number_of_copies != 0)
    {
        std::cout << "Creating more then one GFLW context is not allowed" << std::endl;
        return;
    }

    if (!glfwInit())
    {
        std::cerr << "ERROR:: glfl initialization failed!" << std::endl;
        throw std::runtime_error{ "EXCEPTION:: glfl initialization failed!" };
    }

    ++number_of_copies;

    /* Setup version of OpenGL. If not compared then terminated */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Resources::GFLW_Wrap::~GFLW_Wrap()
{
    glfwTerminate();
}
