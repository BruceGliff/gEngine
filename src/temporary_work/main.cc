#include "ResourceManager.h"

int main() {
    ResMgr M{};

    std::string name {"rock_texture"};
    
    Material::Texture * t =  M.loadTexture("/there/is/long/path", name);
    Material::Material & m = *M.loadMaterial("material");

    m.Set(M.loadTexture("rock_texture"), Material::MaterialType::Ambient);

    m.Set(t, Material::MaterialType::Diffuse);
    Material::IMaterialNode & node = m.Set(Material::Color{255, 128, 15}, Material::MaterialType::Specular);

    std::cout << "asd " << node.get<Material::Texture>().dump() << "\n";

}