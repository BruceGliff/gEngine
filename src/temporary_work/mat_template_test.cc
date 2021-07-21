#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <cstring>

struct Color {
    float a{1.f},b{2.f},c{3.f},d{4.f};
    Color() {std::cout << "Color\n";};
};

// This is actually pointer in real case. Texture *
struct pTexture {
    double a {5.};
    pTexture() {std::cout << "Texture\n";};
};
struct Error {
    Error() = delete;
};


struct alignas(sizeof(Color)) pTextureAligned {
    pTexture m_pTextureAligned {};
};

template <typename T>
struct NodeComponentResolver : public Error {};

template <>
struct NodeComponentResolver<Color> : public Color {};

template <>
struct NodeComponentResolver<pTexture> : public pTextureAligned {};

struct IMaterialComponentTy {
    virtual void process() = 0;
};

struct Diffuse : IMaterialComponentTy {
    void process() override {};
};

// NodeComponent = Texture*, Color
// NodeComponentResolved = Color/pTextureAligned
template <
    typename NodeComponent,
    typename T = NodeComponentResolver<NodeComponent>
>
class IMaterialNode final {
    T m_Component{};    // in case of pTexture it contains pointer to real texture
                        // in case of Color it contains COPY of real color

public:
    IMaterialNode(NodeComponent const & Component)
        : m_Component{Component} {}
    
    NodeComponent * get() {
        if constexpr (std::is_same<NodeComponent, Color>()) {
            std::cout << "Getting Color" << std::endl;
            return &m_Component;
        }
        if constexpr (std::is_same<NodeComponent, pTexture>()) {
            std::cout << "Getting Texture" << std::endl;
            return &m_Component.m_pTextureAligned;
        }
    }
};


struct MaterialNodeSubstance final {
    float m_Component[sizeof(Color) / sizeof(float)]; // It is Color OR pTextureAligned depends on type_index;

    MaterialNodeSubstance(pTexture tex) {
        pTextureAligned p {tex};
        float * data = reinterpret_cast<float *>(&p);
        std::memcpy(m_Component, data, sizeof(m_Component));
    }
    MaterialNodeSubstance(Color const & col) {
        float const * data = reinterpret_cast<float const *>(&col);
        std::memcpy(m_Component, data, sizeof(m_Component));
    }
};

class Material final {
    // map of Diffuse and Color/Texture
    std::unordered_map<std::type_index, MaterialNodeSubstance> m_material;

public:
    template <typename NodeTy>
    IMaterialNode<pTexture> & Set(pTexture texture) {
        auto [it, isOk] = m_material.insert_or_assign(  std::type_index(typeid(NodeTy)), // Diffuse in map
                                                        texture                          // poiter to texture
                                                      );
        return *reinterpret_cast<IMaterialNode<pTexture> *>(it->second.m_Component);
        //return IMaterialNode<pTexture>{texture};
    }

    template <typename NodeTy>
    IMaterialNode<Color> Set(Color const & color) {
        auto [it, isOk] = m_material.insert_or_assign(  std::type_index(typeid(NodeTy)), // Diffuse in map
                                                        color                            // Color
                                                      );
        return *reinterpret_cast<IMaterialNode<Color> *>(it->second.m_Component);
    }

    void process() {
        for (auto && n : m_material) {
            
        }
    }

};


int main() {

    Material mat{};


    // compilation error
    //IMaterialNode<int, bool>{};
}
