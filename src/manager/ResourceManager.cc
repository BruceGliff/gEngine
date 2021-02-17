#include "ResourceManager.h"
#include "../renderer/ShaderProgram.h"
#include "../renderer/TextureGL.h"
#include "../debug/debug.h"
#include "../model/mesh_base.h"

#include <iostream>
#include <sstream>
#include <fstream>


std::string Resources::ResourcesManager::readFile(std::filesystem::path const& relativePath) const
{
    std::ifstream file{ path_to_exec / relativePath, std::ios::in | std::ios::binary};
    if (!file.is_open())
    {
        gERROR(std::string{ "Cannot read file: " + relativePath.lexically_normal().string() });
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

    gWARNING(std::string("No shader program with name: ") + shaderName);
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

std::shared_ptr<Model::Model> Resources::ResourcesManager::loadModel(std::string const& modelName, std::filesystem::path const& relevantPath)
{
    ModelMap::const_iterator it = models.find(modelName);
    // if model does not exist, then load it
    if (it == models.end())
        return models.emplace(modelName, std::make_shared<Model::Model>(path_to_exec / relevantPath)).first->second;

    // if model already exists, return it
    return it->second;
}

std::shared_ptr<Model::Model> Resources::ResourcesManager::getModel(std::string const& modelName) const noexcept
{
    ModelMap::const_iterator it = models.find(modelName);
    // if model does not exist, then load it
    if (it != models.end())
        return it->second;

    gWARNING(std::string{ "No texture with name: " } + modelName);
    return nullptr;
}

std::shared_ptr<Renderer::TextureGL> Resources::ResourcesManager::getTexture(std::string const& textureName) const noexcept
{
    TexturesMap::const_iterator it = textures.find(textureName);
    if (it != textures.end())
    {
        return it->second;
    }

    gWARNING(std::string("No texture with name: ") + textureName);
    return nullptr;
}

std::filesystem::path const& Resources::ResourcesManager::getPathToExucutable() const
{
    return path_to_exec;
}
