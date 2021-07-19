#include "model/primitives.h"

template<typename T, typename ... Args>
Model::IModel * Resources::ResourcesManager::loadModel(Args && ... args)
{
    if constexpr (std::is_base_of<Model::Primitive, T>::value) {
        return loadPrimitive<T>(args ...);
    } else {
        return loadMesh<T>(args ...);
    }
}

template<typename T, typename ... Args>
Model::IModel * Resources::ResourcesManager::loadPrimitive(Args && ... args)
{
    // primitive's names depend on class name 
    std::string const modelName = std::string{"some_pretty_hashick2735_"} + typeid(T).name();
    ModelMap::const_iterator it = m_Models.find(modelName);
    if (it == m_Models.end()) {
        T * p = T::Create(args ...);
        Model::IModel * pM = static_cast<Model::IModel *>(p);    
        if (!pM) {
            delete p;
            gWARNING(std::string{"This is not suppose to happen: Check with is_base_of<>() gave wrong result!\n "} + typeid(T).name());
            return nullptr;
        }
        return m_Models.emplace(modelName, pM).first->second.get();
    }
    return it->second.get();
}

template<typename T>
Model::IModel * Resources::ResourcesManager::loadMesh(std::string const & modelName, std::filesystem::path const& relevantPath)
{
    ModelMap::const_iterator it = m_Models.find(modelName);
    // if model does not exist, then load it
    if (it == m_Models.end()) {
        return m_Models.emplace(modelName, std::make_unique<Model::Model3D>(path_to_exec / relevantPath)).first->second.get();
    }
    
    // if model already exists, return it
    return it->second.get();
    
}