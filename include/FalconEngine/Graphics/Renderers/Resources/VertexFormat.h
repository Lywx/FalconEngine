#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

namespace FalconEngine
{

class VertexBuffer;
class VertexFormat : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VertexFormat();
    virtual ~VertexFormat();

private:
    VertexBuffer *mVertexBuffer;
};

using VertexFormatSharedPtr = std::shared_ptr<VertexFormat>;
}
