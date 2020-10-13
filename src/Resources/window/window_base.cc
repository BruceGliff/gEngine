#include "window_base.h"

#include <iostream>
#include <exception>

// This is CRUTCH
// TODO make it more commot with OOP
namespace global
{
    int g_x = 0;
    int g_y = 0;
}


Resources::glWindows::glWindows() : glWindows(1000, 800, "gEngine")
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

void Resources::glWindows::glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    global::g_x = width;
    global::g_y = height;
    glViewport(0, 0, global::g_x, global::g_y);
}

void Resources::glWindows::glfwKeyCallback(GLFWwindow* window, int key, int scanmode, int action, int mode)
{
    // Close window due to escape
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        // Set up window property what is has to be closed
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
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
