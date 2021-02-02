#include "EnvironmentHandler_wrap.h"

#include "ResourceManager.h"
#include "../window/window_base.h"

#include <iostream>
#include <exception>

Resources::EnvironmentHandler_wrap::EnvironmentHandler_wrap() noexcept
{
}

void Resources::EnvironmentHandler_wrap::construct(int width, int height, std::string const& WindowName, std::string const& path_to_exec)
{
    // Order is important
    glfwInitialization();
    ConstructWindow(width, height, WindowName);
    ConstructManager(path_to_exec);
}

void Resources::EnvironmentHandler_wrap::glfwInitialization()
{
    static int number_of_copies = 0;
    if (number_of_copies != 0)
    {
        std::cout << "WARN:: Creating more then one GFLW context is not allowed" << std::endl;
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

void Resources::EnvironmentHandler_wrap::ConstructManager(std::string const& path_to_exec)
{
    static int counter = 0;
    if (!counter)
    {
        curr_mng = new ResourcesManager{ path_to_exec };
        ++counter;
    }
    else
        std::cout << "WARN:: attempt to create new Resource Manager" << std::endl;
}
void Resources::EnvironmentHandler_wrap::ConstructWindow(int width, int height, std::string const& WindowName)
{
    static int counter = 0;
    if (!counter)
    {
        curr_window = new glWindow{ width, height, WindowName };
        ++counter;
    }
    else
        std::cout << "WARN:: attempt to create new window" << std::endl;
}

Resources::ResourcesManager& Resources::EnvironmentHandler_wrap::GetMenager()
{
    if (curr_mng)
        return *curr_mng;

    std::cerr << "ERR:: Attemt to get null Resource Manager!" << std::endl;
    throw std::runtime_error{ "ERR:: Attemt to get null Resource Manager!" };
}

Resources::ResourcesManager const& Resources::EnvironmentHandler_wrap::GetMenager() const
{
    if (curr_mng)
        return *curr_mng;

    std::cerr << "ERR:: Attemt to get null Resource Manager!" << std::endl;
    throw std::runtime_error{ "ERR:: Attemt to get null Resource Manager!" };
}

Resources::glWindow& Resources::EnvironmentHandler_wrap::GetWindow()
{
    if (!curr_window)
    {
        std::cerr << "ERR:: Attemt to Get null window!" << std::endl;
        throw std::runtime_error{ "ERR:: Attemt to Get null window!" };
    }
    return *curr_window;
}

Resources::glWindow const& Resources::EnvironmentHandler_wrap::GetWindow() const
{
    if (!curr_window)
    {
        std::cerr << "ERR:: Attemt to Get null window!" << std::endl;
        throw std::runtime_error{ "ERR:: Attemt to Get null window!" };
    }
    return *curr_window;
}


Resources::EnvironmentHandler_wrap::~EnvironmentHandler_wrap()
{
    // Order is important
    if (curr_mng)
        delete curr_mng;
    else
        std::cerr << "WARN:: Somehow nullptr of ResourcesManager apprears in ~EnvironmentHandler_wrap()!" << std::endl;
    if (curr_window)
        delete curr_window;
    else
        std::cerr << "WARN:: Somehow nullptr of glWindow apprears in ~EnvironmentHandler_wrap()!" << std::endl;

    glfwTerminate();

}
