#pragma once

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderer/Resources/VertexAttribute.h>

namespace FalconEngine
{

enum class VertexAttributeType;
using VertexAttributeVector = std::vector<VertexAttribute>;

class VertexFormat
{
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
    PushVertexAttribute(int attributeLocation, std::string attributeName, VertexAttributeType attributeType, bool attributeNormalized, int attributeBindingIndex, int attributeDivision = 0);

    void
    FinishVertexAttribute();

public:
    // NOTE(Wuxiang): The vertex attribute vector is assumed to be in order of
    // layout location in OpenGL. This rule is enforced by the PushAttribute function.
    VertexAttributeVector mVertexAttributeList;

private:
    int                   mVertexAttributeOffset;
    bool                  mVertexAttributeFinished;

};

using VertexFormatSharedPtr = std::shared_ptr<VertexFormat>;

}
