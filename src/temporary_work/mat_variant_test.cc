#include <iostream>

#include "material/material.h"



int main() {
    Material::Material mat{};
    mat.Set<Material::Diffuse>(Material::pTexture{});
    Material::Color & tmp = *mat.Set<Material::Ambient>(Material::Color{125, 255, 0});

    Material::IMaterialNode & n = mat.Get<Material::Ambient>();
    std::cout << *n.get<Material::Color>() << std::endl;    
}
