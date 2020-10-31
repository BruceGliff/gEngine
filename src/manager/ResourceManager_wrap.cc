#include "ResourceManager_wrap.h"
#include "ResourceManager.h"

#include <iostream>
#include <exception>

Resources::ResourcesManager_wrap::ResourcesManager_wrap() noexcept
{
}

void Resources::ResourcesManager_wrap::construct(std::string const& path_to_exec)
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

Resources::ResourcesManager& Resources::ResourcesManager_wrap::GetMenager()
{
    if (curr_mng)
        return *curr_mng;

    std::cerr << "ERR:: Attemt to get null Resource Manager!" << std::endl;
    throw std::runtime_error{ "ERR:: Attemt to get null Resource Manager!" };
}

Resources::ResourcesManager const& Resources::ResourcesManager_wrap::GetMenager() const
{
    if (curr_mng)
        return *curr_mng;

    std::cerr << "ERR:: Attemt to get null Resource Manager!" << std::endl;
    throw std::runtime_error{ "ERR:: Attemt to get null Resource Manager!" };
}

Resources::ResourcesManager_wrap::~ResourcesManager_wrap()
{
    if (curr_mng)
        delete curr_mng;
}
