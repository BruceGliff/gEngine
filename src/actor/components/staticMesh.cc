#include "staticMesh.h"
#include "../../model/mesh_base.h"

Component::StaticMesh::StaticMesh(std::filesystem::path const& path)
{
    model = new Model::Model{path};
}

Component::StaticMesh::~StaticMesh()
{
    delete model;
}

