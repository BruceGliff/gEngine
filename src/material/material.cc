#include "material.h"

#include "texture.h"
#include "../renderer/ShaderProgram.h"

using namespace NSMaterial;


IMaterialNode::IMaterialNode(Texture * texture) : m_Component{texture} {}
IMaterialNode::IMaterialNode(Color const & color) : m_Component{color} {}
IMaterialNode::IMaterialNode(IMaterialNode && other) noexcept : m_Component{std::move(other.m_Component)} {}

IMaterialNode & IMaterialNode::operator=(IMaterialNode && other) noexcept {
  std::swap(m_Component, other.m_Component);
  return *this;
}

void IMaterialNode::activate(char const * prefix, unsigned offset, NSRenderer::ShaderProgram const & shader) const {
    if (std::holds_alternative<Color>(m_Component))
        std::get<Color>(m_Component).activate(prefix, offset, shader);
    else
        std::get<Texture*>(m_Component)->activate(prefix, offset, shader);
}

void Material::process(NSRenderer::ShaderProgram const & shader) const {
    unsigned offset {0};
    for (auto && n : m_Material)
        n.second.activate(n.first->getPrefix(), offset++, shader);
}