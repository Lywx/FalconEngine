#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexAttribute.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>

namespace FalconEngine
{

enum class VertexAttributeType;

class VertexFormat : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VertexFormat();
    virtual ~VertexFormat();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/

    /************************************************************************/
    /* Vertex Attribute Management                                          */
    /************************************************************************/
    int
    GetVertexAttributeNum() const;

    VertexAttribute&
    GetVertexAttribute(int attributeIndex);

    int
    GetVertexAttributeStride() const;

    void
    PushVertexAttribute(int attributeLocation, std::string attributeName, VertexAttributeType attributeType, bool attributeNormalized, int attributeBindingIndex);

    void
    FinishVertexAttribute();

public:
    // NOTE(Wuxiang): The vertex attribute vector is assumed to be in order of
    // layout location in OpenGL. This rule is enforced by the PushAttribute function.
    VertexAttributeVector    mVertexAttributeVector;

private:
    int                      mVertexAttributeOffset;
    bool                     mVertexAttributeFinished;

};

using VertexFormatSharedPtr = std::shared_ptr<VertexFormat>;

}
