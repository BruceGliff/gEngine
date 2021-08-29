#include "../model/primitives.h"

template<typename T, typename ... Args>
NSModel::IModel * NSResources::ResourcesManager::loadModel(Args && ... args) {
    if constexpr (std::is_base_of<NSModel::Primitive, T>::value)
        return loadPrimitive<T>(args ...);
    else
        return loadMesh<T>(args ...);
}

template<typename T, typename ... Args>
NSModel::IModel *  NSResources::ResourcesManager::loadPrimitive(Args && ... args) {
    //primitive's names depend on class name 
    std::string const modelName = std::string{"some_pretty_hashick2735_"} + typeid(T).name();
    ModelMap::const_iterator it = m_Models.find(modelName);
    // if prim does not exist, then load it
    if (it == m_Models.end())
        return m_Models.emplace(modelName, std::make_unique<T>()).first->second.get();    
    // if prim already exists, return it
    return it->second.get();
}

template<typename T>
NSModel::IModel *  NSResources::ResourcesManager::loadMesh(std::string const & modelName, std::filesystem::path const& relevantPath) {
    ModelMap::const_iterator it = m_Models.find(modelName);
    // if model does not exist, then load it
    if (it == m_Models.end())
        return m_Models.emplace(modelName, std::make_unique<NSModel::Model3D>(m_PathToExecutable / relevantPath)).first->second.get();    
    // if model already exists, return it
    return it->second.get();
    
}