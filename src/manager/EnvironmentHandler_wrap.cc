#include "EnvironmentHandler_wrap.h"

#include "debug/debug.h"

#include "ResourceManager.h"
#include "window/window_base.h"

#include <iostream>

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
        gWARNING("Creating more then one GFLW context is not allowed");
        return;
    }

    if (!glfwInit())
    {
        gERROR("glfl initialization failed!");
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
        gWARNING("attempt to create new ResourceManager");
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
        gWARNING("attempt to create new glWindow"); // TODO there may be a way to creating lots of windows
}

Resources::ResourcesManager& Resources::EnvironmentHandler_wrap::GetMenager()
{
    if (curr_mng)
        return *curr_mng;

    gERROR("Attemt to get null ResourceManager!");
}

Resources::ResourcesManager const& Resources::EnvironmentHandler_wrap::GetMenager() const
{
    if (curr_mng)
        return *curr_mng;

    gERROR("Attemt to get null ResourceManager!");
}

Resources::glWindow& Resources::EnvironmentHandler_wrap::GetWindow()
{
    if (curr_window)
    {
        return *curr_window;
    }
    
    gERROR("Attemt to get null glWindow!");
}

Resources::glWindow const& Resources::EnvironmentHandler_wrap::GetWindow() const
{
    if (curr_window)
    {
        return *curr_window;
    }

    gERROR("Attemt to get null glWindow!");
}


Resources::EnvironmentHandler_wrap::~EnvironmentHandler_wrap()
{
    // Order is important
    if (curr_mng)
        delete curr_mng;
    else
        gWARNING("Somehow nullptr of ResourcesManager apprears in ~EnvironmentHandler_wrap()!");
    if (curr_window)
        delete curr_window;
    else
        gWARNING("Somehow nullptr of glWindow apprears in ~EnvironmentHandler_wrap()!");

    glfwTerminate();

}
