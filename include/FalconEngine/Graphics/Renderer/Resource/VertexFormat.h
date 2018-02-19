#pragma once

#include <memory>

#include <FalconEngine/Core/Macro.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>

namespace FalconEngine
{

enum class VertexAttributeType;
class VertexGroup;

class Shader;
class ShaderSource;

// @remark Vertex format should be attached to visual level object. In modeling
// software, the vertex format should be attached to any individual object.
// Hence, make the visual the right target to be attached to. Each visual control
// individual object in modeling software, like a bed, a table in a room.
FALCON_ENGINE_CLASS_BEGIN VertexFormat
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    // NOTE(Wuxiang): This constructor should be used for Visual Effect class's
    // vertex format creation. The shader source is used in Direct3D to validate
    // the Input Layout.
    VertexFormat(const std::shared_ptr<Shader>& shader);
    VertexFormat();
    virtual ~VertexFormat();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/

    /************************************************************************/
    /* Vertex Attribute Management                                          */
    /************************************************************************/
    bool
    IsVertexAttributeCompatible(const std::shared_ptr<VertexFormat>& rhs) const;

    bool
    IsVertexAttributeCompatible(const VertexFormat * rhs) const;

    int
    GetVertexAttributeNum() const;

    const VertexAttribute&
    GetVertexAttribute(int attributeIndex) const;

    VertexAttribute&
    GetVertexAttribute(int attributeIndex);

    void
    PushVertexAttribute(int                 attributeLocation,
                        std::string         attributeName,
                        VertexAttributeType attributeType,
                        bool                attributeNormalized,
                        int                 attributeBindingIndex,
                        int                 attributeDivision = 0);

    void
    FinishVertexAttribute();

    /************************************************************************/
    /* Vertex Buffer Management                                             */
    /************************************************************************/
    bool
    IsVertexBindingCompatible(const std::shared_ptr<VertexGroup>& rhs) const;

    bool
    IsVertexBindingCompatible(const VertexGroup * rhs) const;

    int
    GetVertexBufferStride(int attributeBindingIndex) const;

    /************************************************************************/
    /* Vertex Shader Management                                             */
    /************************************************************************/
    ShaderSource *
    GetVertexShader() const;

private:
    std::shared_ptr<Shader> mShader;

    // NOTE(Wuxiang): The vertex attribute vector is assumed to be in order of
    // layout location in OpenGL. This rule is enforced by the PushAttribute
    // function.
    std::vector<VertexAttribute> mVertexAttributeList;

    // NOTE(Wuxiang): Vertex attribute stride list. Each element counts
    // buffer's data total stride in byte, at specific vertex buffer binding
    // index.
    std::vector<int> mVertexAttributeStrideList;

    // NOTE(Wuxiang): This is used as an enforcement for making vertex attribute
    // list immutable once it is set up correctly.
    bool mVertexAttributeFinished = false;
};
FALCON_ENGINE_CLASS_END

}
