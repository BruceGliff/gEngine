#include "ResourceManager.h"
#include "../renderer/ShaderProgram.h"
#include "../renderer/TextureGL.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>


std::string Resources::ResourcesManager::readFile(std::filesystem::path const& relativePath) const
{
    std::ifstream file{ path_to_exec / relativePath, std::ios::in | std::ios::binary};
    if (!file.is_open())
    {
        std::cerr << "ERROR:: file reading\n" << "cannot read file < " << relativePath.lexically_normal() << " >" << std::endl;
        throw std::runtime_error{ "ERROR:: file reading" };
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

Resources::ResourcesManager::ResourcesManager(std::filesystem::path const& execPath) : 
    path_to_exec{ std::filesystem::path{execPath}.remove_filename() }
{}


std::shared_ptr<Renderer::ShaderProgram> Resources::ResourcesManager::loadShaders(  std::string const& shaderName, 
                                                                                    std::filesystem::path const& vertexPath, 
                                                                                    std::filesystem::path const& fragmentPath)
{
    std::string const vertexCode{ readFile(vertexPath) };
    std::string const fragmentCode{ readFile(fragmentPath) };

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

std::shared_ptr<Renderer::TextureGL> Resources::ResourcesManager::loadTexture(std::filesystem::path const& relevantPath, Renderer::ETextureType texType)
{
    std::filesystem::path const absolutePath{ path_to_exec / relevantPath };
    
    TexturesMap::const_iterator it = textures.find(absolutePath);

    // if texture does not exist, then load it
    if (it == textures.end())
        return textures.emplace(absolutePath, std::make_shared<Renderer::TextureGL>(absolutePath, texType)).first->second;

    // if texture already exists, return it
    return it->second;
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

std::filesystem::path const& Resources::ResourcesManager::getPathToExucutable() const
{
    return path_to_exec;
}
