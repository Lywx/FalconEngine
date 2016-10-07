#pragma once

#include <FalconEngine/Geometry/Geometry.h>
#include <FalconEngine/Geometry/TriangleMesh.h>

namespace FalconEngine {

class TriangleMesh;
class TriangleGeometry : public Geometry
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    TriangleGeometry();
    TriangleGeometry(const TriangleMeshPtr mesh);

    virtual ~TriangleGeometry();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    virtual void SetMesh(const MeshPtr mesh) override;

private:
    TriangleMeshPtr m_mesh;
};

typedef std::shared_ptr<TriangleGeometry> TriangleGeometryPtr;

}
