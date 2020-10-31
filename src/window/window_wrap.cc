#include "window_wrap.h"
#include "window_base.h"

#include <iostream>
#include <exception>

Resources::windows_wrap::windows_wrap() noexcept
{}

void Resources::windows_wrap::construct(int width, int height, std::string const& WindowName)
{
    static int counter = 0;
    if (!counter)
    {
        curr_window = new glWindows{ width, height, WindowName };
        ++counter;
    }
    else
        std::cout << "WARN:: attempt to create new window" << std::endl;
}

Resources::glWindows& Resources::windows_wrap::GetWindow()
{
    if (!curr_window)
    {
        std::cerr << "ERR:: Attemt to Get null window!" << std::endl;
        throw std::runtime_error{ "ERR:: Attemt to Get null window!" };
    }
    return *curr_window;
}

Resources::glWindows const& Resources::windows_wrap::GetWindow() const
{
    if (!curr_window)
    {
        std::cerr << "ERR:: Attemt to Get null window!" << std::endl;
        throw std::runtime_error{ "ERR:: Attemt to Get null window!" };
    }
    return *curr_window;
}

Resources::windows_wrap::~windows_wrap()
{
    if (curr_window)
        delete curr_window;
}
