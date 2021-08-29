#pragma once

#include "../../manager/Entity.h"
#include "../../properties/properties.h"

namespace NSModel {
    class IModel;
} // namespace NSModel
namespace NSMaterial {
    class TextureCube;
} // namespace NSMaterial

namespace NSScene {

class Skybox final
    : public NSResources::Entity
    , public NSProperty::ICompound
    , public NSProperty::IDrawable {

    NSModel::IModel * m_CubeModel {};
    NSMaterial::TextureCube * m_TextureCube {};

public:
    Skybox(NSMaterial::TextureCube * Texture) noexcept;

    Skybox();
    Skybox(Skybox const & )             = delete;
    Skybox(Skybox&&)                    = delete;
    Skybox & operator=(Skybox const &)  = delete;
    Skybox & operator=(Skybox &&)       = delete;

    void SetTexture(NSMaterial::TextureCube * Texture) noexcept;
    void Draw(NSGeometry::Transformation const & tr) override;
};

} // namespace NSScene;