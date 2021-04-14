#pragma once

#include <memory>
#include "mesh_base.h"

namespace Model {

    class Primitive {
	protected:
		Primitive() {}
		std::unique_ptr<Mesh> mesh;

        virtual std::vector<Vertex> 	  generateVertices() = 0;
        virtual std::vector<unsigned int> generateIndices()  = 0;
	public:
		virtual ~Primitive() {}
	};

    class Plane final : public IModel,
                        public Primitive {

        std::vector<Vertex> 				generateVertices() override;
        std::vector<unsigned int> 			generateIndices()  override;
    public:
        Plane();
        Plane(std::vector<Renderer::TextureGL*> const & texturesIn);
        void Draw(Renderer::ShaderProgram const & shader) const override;

        // TODO
    };
} // namespace gEng