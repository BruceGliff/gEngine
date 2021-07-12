#include <variant>
#include <unordered_map>
#include <iostream>

struct Color {
    float a{1.f},b{2.f},c{3.f},d{4.f};
    Color() {std::cout << "Color\n";};
};

struct pTexture {
    float a {5.f};
    pTexture() {std::cout << "Texture\n";};
};


struct IMaterialComponentTy {
    virtual void process() {}
    virtual bool operator==(IMaterialComponentTy const & other) const noexcept {return false; }
    virtual int getID() const noexcept { return -1; }
};

struct Diffuse : IMaterialComponentTy {
    int const ID {0};
    int getID() const noexcept override { return ID; }
    void process() override {}

    bool operator==(IMaterialComponentTy const & other) const noexcept override {
        return other.getID() == getID();
    }
};
struct Ambient : IMaterialComponentTy {
    int const ID {1};
    int getID() const noexcept override { return ID; }
    void process() override {}

    bool operator==(IMaterialComponentTy const & other) const noexcept override  {
        return other.getID() == getID();
    }
};


struct _ColorTypesHolder { // make it singletone
    Diffuse m_dif{};
    Ambient m_amb{};
} ColorTypesHolder;

template <typename T>
T * getCType() { return nullptr;}

template <> Diffuse * getCType<Diffuse>() { return &ColorTypesHolder.m_dif; };
template <> Ambient * getCType<Ambient>() { return &ColorTypesHolder.m_amb; };


namespace std {
  template <> struct hash<IMaterialComponentTy> {
    std::size_t operator()(IMaterialComponentTy const & comp) const {
      return std::hash<int>()(comp.getID());
    }
  };

}

struct IMaterialNode final {
    std::variant<Color, pTexture> m_Component {};

public:
    IMaterialNode(pTexture tex)
        : m_Component{tex} {}

    IMaterialNode(Color const & col)
        : m_Component{col} {}

    template <typename T>
    T * get() {
        if constexpr (std::is_same<Color, T>::value) {
            return std::get_if<Color>(&m_Component);
        }
        if constexpr(std::is_same<pTexture, T>::value) {
            return std::get_if<pTexture>(&m_Component);// TODO:: make *std::get_if and addition check on nullptr
        }

        return nullptr;
    }
};

class Material final {
    // map of Diffuse and Color/Texture
    typedef std::unordered_map<IMaterialComponentTy *, IMaterialNode> MaterialMap;
    MaterialMap m_Material;

public:
    template <class NodeTy>
    pTexture * Set(pTexture texture) {
        auto [it, isOk] = m_Material.insert_or_assign(getCType<NodeTy>(), texture);
        std::cout << it->first->getID() << std::endl;
        pTexture * p = std::get_if<pTexture>(&it->second.m_Component);// there will be **p
        if (p) return p;
        else return nullptr;
    }

    template <typename NodeTy>
    Color * Set(Color const & color) {
        auto [it, isOk] = m_Material.insert_or_assign(getCType<NodeTy>(), color);
        return it->second.template get<Color>();
    }

    void process() {
        for (auto && n : m_Material) {
            
        }
    }

    template <typename NodeTy>
    IMaterialNode & Get() {
        MaterialMap::iterator it = m_Material.find(getCType<NodeTy>());
        if (it == m_Material.end()) {
            std::cout << "No such TYPE" << typeid(NodeTy).name() << "\n";
        }

        return it->second;
    }

};


int main() {
    Material mat{};
    mat.Set<Diffuse>(pTexture{});
    Color & tmp = *mat.Set<Ambient>(Color{});

    IMaterialNode & n = mat.Get<Ambient>();
    std::cout << n.get<Color>()->b << std::endl;

    //std::cout << tmp.c << std::endl;

    
}
