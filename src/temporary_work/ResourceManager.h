#pragma once

#include "material.h"
#include "texture.h"
// TODO imclude GL_LINEAR and GL_CLAMP_TO_EDGE
unsigned GL_LINEAR = 0;
unsigned GL_CLAMP_TO_EDGE = 0;

#include <unordered_map>
#include <string>
#include <memory>
#include <filesystem>
#include <iostream>

class ResMgr final {
    // resmgr has handle also material
    // Models textures materials have to be unique by name

    // textures unique by name!
    typedef std::unordered_map<std::string, std::unique_ptr<Material::Texture>> TextureMap;
    TextureMap m_Textures;
    
    typedef std::unordered_map<std::string, std::unique_ptr<Material::Material>> MaterialMap;
    MaterialMap m_Materials;



public:
    Material::Texture * loadTexture(std::filesystem::path const& relevantPath, std::string const & texture_name) {
        if (Material::Texture * pT = loadTexture(texture_name, true)) {
            return pT;
        }
        return m_Textures.emplace(texture_name, std::make_unique<Material::Texture>(relevantPath, GL_LINEAR, GL_CLAMP_TO_EDGE)).first->second.get();
    }
    // loads texture what already has been loaded. Return nullptr if there is no such texture
    Material::Texture * loadTexture(std::string const & texture_name, bool no_warning = false) {
        TextureMap::const_iterator it = m_Textures.find(texture_name);
        if (it == m_Textures.end()) {
            if (!no_warning) {
                // DO WARNINGS
            }
            return nullptr;
        }
        return it->second.get();
    }

    // its loads existed or generates empty material
    Material::Material * loadMaterial(std::string const & material_name) {
        MaterialMap::const_iterator it = m_Materials.find(material_name);
        if (it == m_Materials.end()) {
            return m_Materials.emplace(material_name, std::make_unique<Material::Material>()).first->second.get();
        }
        return it->second.get();
    }


};