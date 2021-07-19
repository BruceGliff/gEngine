// IMaterialNode
template <typename T>
T * IMaterialNode::get() noexcept {
    if constexpr (std::is_same<Color, T>::value)
        return std::get_if<Color>(&m_Component);
    if constexpr(std::is_same<Texture, T>::value) {
        Texture ** ppTexture = std::get_if<Texture*>(&m_Component);
        return ppTexture ? *ppTexture : nullptr;
    }
    gWARNING(std::string{"Getting non Color and non Texture: "} + typeid(T).name());
    return nullptr;
}

// Material
template <class NodeTy>
Texture * Material::Set(Texture * texture) {
    auto [it, isOk] = m_Material.insert_or_assign(getComponentTy<NodeTy>(), texture);
    if (!isOk) {
      gWARNING("Insertion node to material fails!");
      return nullptr;
    }
    return it->second.template get<Texture>();
}

template <typename NodeTy>
Color * Material::Set(Color const & color) {
    auto [it, isOk] = m_Material.insert_or_assign(getComponentTy<NodeTy>(), color);
    if (!isOk) {
      gWARNING("Insertion node to material fails!");
      return nullptr;
    }
    return it->second.template get<Color>();
}

template <typename NodeTy>
IMaterialNode & Material::Get() {
    MaterialMap::iterator it = m_Material.find(getComponentTy<NodeTy>());
    if (it == m_Material.end())
      gERROR(std::string{"No such Component's type in material: "} + typeid(NodeTy).name());
    return it->second;
}