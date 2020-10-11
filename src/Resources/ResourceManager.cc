#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>

#define STBI_ONLY_JPEG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::string Resources::ResourcesManager::computePath(std::string const & path) const
{
    size_t const slash_position = path.find_last_of("/\\");
    if (slash_position == std::string::npos)
    {
        std::cerr << "ERROR:: path parse\n" << "cannot find '/' or '\\' in < " << path << " >" << std::endl;
        throw std::runtime_error{ "ERROR:: path parse" };
    }

    return path.substr(0, slash_position);
}

std::string Resources::ResourcesManager::getFile(std::string const& relativePath) const
{
    std::ifstream file{ path + "/" + relativePath.c_str(), std::ios::in | std::ios::binary};
    if (!file.is_open())
    {
        std::cerr << "ERROR:: file reading\n" << "cannot read file < " << relativePath << " >" << std::endl;
        throw std::runtime_error{ "ERROR:: file reading" };
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

Resources::ResourcesManager::ResourcesManager(std::string const& execPath) : path{computePath(execPath)}
{}

std::shared_ptr<Renderer::ShaderProgram> Resources::ResourcesManager::loadShaders(std::string const& shaderName, std::string const& vertexPath, std::string const& fragmentPath)
{
    std::string const vertexCode{ getFile(vertexPath) };
    std::string const fragmentCode{ getFile(fragmentPath) };

    // shader can be not compiled!
    return shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexCode, fragmentCode)).first->second;
}

std::shared_ptr<Renderer::ShaderProgram> Resources::ResourcesManager::getShaderProgram(std::string const& shaderName) const noexcept
{
    ShaderProgramsMap::const_iterator it = shaderPrograms.find(shaderName);
    if (it != shaderPrograms.end())
    {
        return it->second;
    }

    std::cerr << "ERROR:: run-time:\n" << "No shader program with name: " << shaderName << std::endl;
    return nullptr;
}

void Resources::ResourcesManager::loadTexture(std::string const& textureName, std::string const& relevantPath) const noexcept
{
    int channels = 0;
    int width = 0;
    int height = 0;

    // Load texture upside down
    stbi_set_flip_vertically_on_load(true);
    unsigned char* rawCode = stbi_load(std::string{ path + '/' + relevantPath }.c_str(), &width, &height, &channels, 0);

    if (!rawCode)
    {
        std::cerr << "ERROR:: run-time:\n" << "Can not load texture: " << relevantPath;
        return;
    }

    stbi_image_free(rawCode);
}
