#pragma once

#include <memory>
#include <string>
#include "mesh_base.h"

#include "../process/global.h"
#include "../manager/ResourceManager.h"

namespace Model {

    class Primitive : public IModel{
	protected:
        Primitive(  std::vector<Renderer::TextureGL*> const & texturesIn,
                    std::string const & name);
		std::unique_ptr<Mesh> mesh;

	public:
        void Draw(Renderer::ShaderProgram const & shader) const override;
		virtual ~Primitive() {}
	};

    #include "primitives.DEF"
    CONTRUCT_PRIMITIVE(Plane);
    CONTRUCT_PRIMITIVE(Cube);
    
    #undef CONTRUCT_PRIMITIVE
} // namespace Model

