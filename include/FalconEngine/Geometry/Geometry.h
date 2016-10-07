#pragma once

#include <FalconEngine/Graphics/Scenes/Visual.h>
#include <FalconEngine/Geometry/Mesh.h>

namespace FalconEngine {

class Geometry : public Visual
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Geometry();
    Geometry(const MeshPtr mesh);

    virtual ~Geometry();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    virtual void SetMesh(const MeshPtr mesh);
    virtual void RenderMesh(double elapsed);
};

typedef std::shared_ptr<Geometry> GeometryPtr;

}