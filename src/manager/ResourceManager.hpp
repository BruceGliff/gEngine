#include "model/primitives.h"

template <typename T>
Model::IModel * Resources::ResourcesManager::load(std::string const & modelName, std::filesystem::path const& relevantPath) {
    ModelMap::const_iterator it = models.find(modelName);
    // if model does not exist, then load it
    if (it == models.end()) {
        return models.emplace(modelName, std::make_unique<T>(path_to_exec / relevantPath)).first->second.get();
    }
    
    // if model already exists, return it
    return it->second.get();
}
template <typename T>
Model::IModel * Resources::ResourcesManager::load(std::vector<Renderer::TextureGL *> const & textures)
{
    // We assume that type has to be a primitive
    if (!std::is_base_of<Model::Primitive, T>::value)
    {
        gWARNING(std::string{"Type is not a primitive: "} + typeid(T).name());
        return nullptr;
    }
    std::string const modelName = typeid(T).name();
    ModelMap::const_iterator it = models.find(typeid(T).name());
    if (it == models.end()) {
        T * p = new T{textures};
        Model::IModel * pM = dynamic_cast<Model::IModel *>(p);	
        if (!pM) {
            delete p;
            gWARNING(std::string{"This is not suppose to happen: Check with typeid() gave wrong result!\n "} + typeid(T).name());
            return nullptr;
        }
        return models.emplace(modelName, pM).first->second.get();
    }
    return it->second.get();
}

template<typename T, typename ... Args>
Model::IModel * Resources::ResourcesManager::loadModel(Args && ... args)
{
    return load<T>(args ...);
}