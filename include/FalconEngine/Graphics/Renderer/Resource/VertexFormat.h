#pragma once

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>

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
    GetVertexAttributeStride(int attributeBindingIndex) const;

    void
    PushVertexAttribute(int attributeLocation, std::string attributeName, VertexAttributeType attributeType, bool attributeNormalized, int attributeBindingIndex, int attributeDivision = 0);

    void
    FinishVertexAttribute();

public:
    // NOTE(Wuxiang): The vertex attribute vector is assumed to be in order of
    // layout location in OpenGL. This rule is enforced by the PushAttribute function.
    VertexAttributeVector mVertexAttributeList;

private:
    // NOTE(Wuxiang): Vertex attribute stride list. Each element counts buffer's data total stride in byte, at specific vertex buffer binding index.
    std::vector<int>      mVertexAttributeOffsetList;

    // NOTE(Wuxiang): This is used as an enforcement for making vertex attribute
    // list immutable once it is set up correctly.
    bool                  mVertexAttributeFinished = false;

};

using VertexFormatSharedPtr = std::shared_ptr<VertexFormat>;

}
