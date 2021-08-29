#include "skybox.h"

#include "../../actor/components/camera.h"
#include "../../actor/actor.h"
#include "../../model/model3D.h"
#include "../../material/texture.h"
#include "../../process/global.h"
#include "../../manager/ResourceManager.h"

using namespace NSScene;

void Skybox::SetTexture(NSMaterial::TextureCube * Texture) noexcept {
    m_TextureCube = Texture;
}

Skybox::Skybox()
    : IDrawable { GLOBAL::GetResManager().loadShaders("SkyboxShader", "res/shaders/skybox/skybox.vs", "res/shaders/skybox/skybox.fs") }
    , m_TextureCube {GLOBAL::GetResManager().loadTexture(std::filesystem::path{"res/textures/skybox/lake"}) }
    , m_CubeModel { GLOBAL::GetResManager().loadModel<NSModel::Cube>() } {}

Skybox::Skybox(NSMaterial::TextureCube * Texture) noexcept
    : IDrawable { GLOBAL::GetResManager().loadShaders("SkyboxShader", "res/shaders/skybox/skybox.vs", "res/shaders/skybox/skybox.fs") }
    , m_CubeModel { GLOBAL::GetResManager().loadModel<NSModel::Cube>() } { 
    SetTexture(Texture); 
}

void Skybox::Draw(NSGeometry::Transformation const & tr) {
    glDepthMask(GL_FALSE);
    shader->Use();
    // Optimize it! Probably for each draw iteration, pass this only once for each shader! Same in Grid.cc
    auto mainCam = GLOBAL::GetPlayer().GetComponentByName<NSComponent::camera>("camera"); // bad impl: what if i've named camera "watcher"?
    shader->setMat4("view", glm::mat4(glm::mat3(mainCam->GetViewMatrix())));
    shader->setMat4("projection", mainCam->GetProjectionMatrix());

    m_TextureCube->activate(*shader);
    m_CubeModel->Draw();
    glDepthMask(GL_TRUE);
}