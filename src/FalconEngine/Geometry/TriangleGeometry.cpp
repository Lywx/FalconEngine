#include <FalconEngine/Geometry/TriangleGeometry.h>
#include <FalconEngine/Geometry/TriangleMesh.h>

namespace FalconEngine {
/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
TriangleGeometry::TriangleGeometry()
{
}

TriangleGeometry::TriangleGeometry(const TriangleMeshPtr mesh)
    : Geometry(mesh), m_mesh(mesh)
{
}

TriangleGeometry::~TriangleGeometry()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void TriangleGeometry::SetMesh(const MeshPtr mesh)
{
    m_mesh = mesh;
}

}
