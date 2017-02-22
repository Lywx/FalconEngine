#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <vector>

#include <FalconEngine/Graphics/Renderers/VisualTriangles.h>
#include <FalconEngine/Graphics/Renderers/Resources/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>

namespace FalconEngine
{

class Mesh : public VisualTriangles
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    // @summary Load vertex, normal, texture coordinate, index, texture object.
    Mesh(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, IndexBufferSharedPtr indexBuffer);
    virtual ~Mesh();
};

typedef std::shared_ptr<Mesh> MeshSharedPtr;

}
