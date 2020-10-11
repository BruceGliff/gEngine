#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/TextureGL.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>

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

std::shared_ptr<Renderer::TextureGL> Resources::ResourcesManager::loadTexture(std::string const& textureName, std::string const& relevantPath)
{
    return textures.emplace(textureName, std::make_shared<Renderer::TextureGL>(path + '/' + relevantPath)).first->second;
}

std::shared_ptr<Renderer::TextureGL> Resources::ResourcesManager::getTexture(std::string const& textureName) const noexcept
{
    TexturesMap::const_iterator it = textures.find(textureName);
    if (it != textures.end())
    {
        return it->second;
    }

    std::cerr << "ERROR:: run-time:\n" << "No shader program with name: " << textureName << std::endl;
    return nullptr;
}


