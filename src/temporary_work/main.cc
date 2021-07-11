#include "ResourceManager.h"

int main() {
    ResMgr M{};

    std::string name {"rock_texture"};
    
    Material::Texture * t =  M.loadTexture("C:\\Code\\gEngine\\build\\bin\\Debug\\res\\textures\\weed_pepe.jpg", name);
    Material::Material & m = *M.loadMaterial("material");

    m.Set(M.loadTexture("rock_texture"), Material::MaterialType::Ambient);

    m.Set(t, Material::MaterialType::Diffuse);
    Material::IMaterialNode & node = m.Set({255, 128, 15}, Material::MaterialType::Specular);

    std::cout << "asd " << *node.get<Material::Color>() << "\n";

}