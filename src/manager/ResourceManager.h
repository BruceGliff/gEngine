#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <filesystem>

#include "../debug/debug.h"
// For unique_ptr
#include "../material/texture.h"
#include "../material/material.h"
#include "../renderer/ShaderProgram.h"
#include "../model/mesh_base.h"

namespace NSResources {

// Contains every resourse which has to be loaded once
class ResourcesManager final {
    // Map of the shaders programs
    typedef std::unordered_map<std::string, std::unique_ptr<NSRenderer::ShaderProgram>> ShaderProgramsMap;
    ShaderProgramsMap m_ShaderPrograms;
    // Map of the textures
    typedef std::unordered_map<std::string, std::unique_ptr<NSMaterial::Texture>> TextureMap;
    TextureMap m_Textures;
    // Map of the materials
    typedef std::unordered_map<std::string, std::unique_ptr<NSMaterial::Material>> MaterialMap;
    MaterialMap m_Materials;
    // Map of models
    typedef std::unordered_map<std::string, std::unique_ptr<NSModel::IModel>> ModelMap;
    ModelMap m_Models;

    // Path to executable file
    std::filesystem::path const m_PathToExecutable;

    // reads file from res/ directory fe: readFile(res/shaders/fragment.glsl);
    std::string readFile(std::filesystem::path const& relativePath) const;

    // loads model
    template <typename T>
    NSModel::IModel * loadMesh(std::string const & modelName, std::filesystem::path const& relevantPath);
    // loads primitives
    template <typename T, typename ... Args>
    NSModel::IModel * loadPrimitive(Args && ... args);

public:
    ResourcesManager() = delete;
    ResourcesManager(ResourcesManager const&) = delete;
    ResourcesManager(ResourcesManager&&) = delete;
    ResourcesManager& operator=(ResourcesManager const&) = delete;
    ResourcesManager& operator=(ResourcesManager&&) = delete;

    // Lots of copy
    ResourcesManager(std::filesystem::path const& execPath);

    // Compiles shader program with shaderName from the sources - vertexPath and fragmentPath
    NSRenderer::ShaderProgram * loadShaders(    std::string const& shaderProgramName,
                                                std::filesystem::path const& vertexPath,
                                                std::filesystem::path const& fragmentPath);
    // Returns ShaderProgram by name or nullptr if it did not find (map<>.find() may throw an exception?>
    NSRenderer::ShaderProgram * getShaderProgram(std::string const& shaderProgramName) const noexcept;

    // Loads texture
    NSMaterial::Texture * loadTexture(  std::filesystem::path const& relevantPath, std::string const & texture_name,
                                        GLenum Filter = GL_LINEAR,
                                        GLenum WrapMode = GL_CLAMP_TO_EDGE);
    // Loads default error texture
    NSMaterial::Texture * loadTexture();
    // loads texture what already has been loaded. Return nullptr if there is no such texture
    NSMaterial::Texture * loadTexture(std::string const & texture_name, bool no_warning = false);

    // Gets or generates material
    NSMaterial::Material * loadMaterial(std::string const & material_name);

    // Loads promitives or model3d depends on type T
    template<typename T, typename ... Args>
    NSModel::IModel * loadModel(Args && ... args);
    // Gets model by name. Return null if not found. Usually for Model3D
    NSModel::IModel * getModel(std::string const& name) const noexcept;

    std::filesystem::path const& getPathToExucutable() const;

};

} //namespace NSResources
#include "ResourceManager.hpp"
