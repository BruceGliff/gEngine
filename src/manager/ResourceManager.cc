#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace NSResources;

std::string ResourcesManager::readFile(std::filesystem::path const& relativePath) const {
    std::ifstream file{m_PathToExecutable / relativePath, std::ios::in | std::ios::binary};
    if (!file.is_open())
        gERROR(std::string{ "Cannot read file: " + relativePath.lexically_normal().string() });

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

ResourcesManager::ResourcesManager(std::filesystem::path const& execPath) : 
    m_PathToExecutable{std::filesystem::path{execPath}.remove_filename()} {}

NSRenderer::ShaderProgram * ResourcesManager::loadShaders( std::string const& shaderName, 
                                                           std::filesystem::path const& vertexPath, 
                                                           std::filesystem::path const& fragmentPath) {
    auto && it = m_ShaderPrograms.find(shaderName);
    if (it != m_ShaderPrograms.end())
        return it->second.get(); 

    std::string const vertexCode{ readFile(vertexPath) };
    std::string const fragmentCode{ readFile(fragmentPath) };
    // shader can be not compiled!
    return m_ShaderPrograms.emplace(  shaderName, std::make_unique<NSRenderer::ShaderProgram>(vertexCode, fragmentCode))
                                      .first->second.get();
}

NSRenderer::ShaderProgram * ResourcesManager::getShaderProgram(std::string const& shaderName) const noexcept {
    ShaderProgramsMap::const_iterator it = m_ShaderPrograms.find(shaderName);
    if (it != m_ShaderPrograms.end())
        return it->second.get();

    gWARNING(std::string("No shader program with name: ") + shaderName);
    return nullptr;
}

NSMaterial::Texture * ResourcesManager::loadTexture() {
    TextureMap::const_iterator it = m_Textures.find("empty");
    if (it == m_Textures.end()) {
        return m_Textures.emplace("empty", std::make_unique<NSMaterial::Texture>())
                                .first->second.get();
    }
    return it->second.get();
}

NSMaterial::Texture * ResourcesManager::loadTexture(std::filesystem::path const& relevantPath,
                                                    std::string const & texture_name,
                                                    GLenum Filter,
                                                    GLenum WrapMode) {
    if (NSMaterial::Texture * pT = loadTexture(texture_name, true))
        return pT;
    return m_Textures.emplace(texture_name, std::make_unique<NSMaterial::Texture>(relevantPath, Filter, WrapMode)).first->second.get();
}

NSMaterial::Texture * ResourcesManager::loadTexture(std::string const & texture_name, bool no_warning) {
    TextureMap::const_iterator it = m_Textures.find(texture_name);
    if (it == m_Textures.end()) {
        if (!no_warning)
            gWARNING("Attemp to get unexisted texture: " + texture_name);

        return nullptr;
    }
    return it->second.get();
}

// its loads existed or generates empty material
NSMaterial::Material * ResourcesManager::loadMaterial(std::string const & material_name) {
    MaterialMap::const_iterator it = m_Materials.find(material_name);
    if (it == m_Materials.end())
        return m_Materials.emplace(material_name, std::make_unique<NSMaterial::Material>()).first->second.get();
    return it->second.get();
}

NSModel::IModel * ResourcesManager::getModel(std::string const& modelName) const noexcept {
    ModelMap::const_iterator it = m_Models.find(modelName);
    if (it != m_Models.end())
        return it->second.get();

    gWARNING(std::string{ "No model with name: " } + modelName);
    return nullptr;
}

std::filesystem::path const& ResourcesManager::getPathToExucutable() const {
    return m_PathToExecutable;
}
