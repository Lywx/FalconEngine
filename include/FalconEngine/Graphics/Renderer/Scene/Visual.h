#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <algorithm>
#include <functional>
#include <list>

#include <FalconEngine/Graphics/Renderer/VisualEffectParams.h>
#include <FalconEngine/Graphics/Renderer/Scene/Mesh.h>
#include <FalconEngine/Graphics/Renderer/Scene/Spatial.h>

namespace FalconEngine
{

class Primitive;
class Renderer;
class VertexFormat;
class VisualEffectInstance;

// @summary This class governs the all the information the user would like to draw
// a set of primitives. Visual effect instance in the Visual class represents all
// uniforms, textures, samplers etc used in the draw calls. However, the effect
// instance is not required as long as you are providing another effect instance
// during draw request.
//
// @remark If you would need to process primitive in different ways, the Visual
// class is the ideal place to differentiate when drawing -- transparency, etc
// special treatment information should be stored in this class.
#pragma warning(disable: 4251)
class FALCON_ENGINE_API Visual : public Spatial
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit Visual(const std::shared_ptr<Mesh>& mesh);
    virtual ~Visual();

protected:
    Visual();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/

    /************************************************************************/
    /* Effect Management                                                    */
    /************************************************************************/
    auto
    GetEffectInstanceBegin() const
    {
        return mEffectInstances.cbegin();
    }

    auto
    GetEffectInstanceEnd() const
    {
        return mEffectInstances.end();
    }

    auto
    GetEffectInstanceBegin()
    {
        return mEffectInstances.begin();
    }

    auto
    GetEffectInstanceEnd()
    {
        return mEffectInstances.end();
    }

    auto
    GetEffectParamBegin() const
    {
        return mEffectParamses.cbegin();
    }

    auto
    GetEffectParamEnd() const
    {
        return mEffectParamses.cend();
    }

    auto
    GetEffectParamBegin()
    {
        return mEffectParamses.begin();
    }

    auto
    GetEffectParamEnd()
    {
        return mEffectParamses.end();
    }

    int
    GetEffectInstanceNum() const;

    void
    PushEffectInstance(std::shared_ptr<VisualEffectInstance> effectInstance);

    void
    RemoveEffectInstance(std::shared_ptr<VisualEffectInstance> effectInstance);

    int
    GetEffectParamsNum() const;

    void
    PushEffectParams(std::shared_ptr<VisualEffectParams> effectParmas);

    void
    RemoveEffectParams(std::shared_ptr<VisualEffectParams> effectParmas);

    const VertexFormat *
    GetVertexFormat() const;

    std::shared_ptr<const VertexFormat>
    GetVertexFormat();

    void
    SetVertexFormat(std::shared_ptr<VertexFormat> vertexFormat);

    const VertexGroup *
    GetVertexGroup() const;

    std::shared_ptr<const VertexGroup>
    GetVertexGroup();

    void
    SetVertexGroup(std::shared_ptr<VertexGroup> vertexGroup);

    /************************************************************************/
    /* Mesh Management                                                      */
    /************************************************************************/
    const Mesh *
    GetMesh() const;

    std::shared_ptr<Mesh>
    GetMesh();

    void
    SetMesh(std::shared_ptr<Mesh> mesh);

    /************************************************************************/
    /* Spatial Management                                                   */
    /************************************************************************/
    void
    UpdateWorldTransform(double elapsed) override;

    /************************************************************************/
    /* Deep and Shallow Copy                                                */
    /************************************************************************/
    void
    CopyTo(Visual *lhs) const;

    // @remark This method use return type covariance in the class hierarchy.
    // @return The clone of this Visual instance. Grant for no shared ownership.
    virtual Visual *
    GetClone() const override;

    // @summary Use a custom function to copy rhs's content into lhs.
    virtual Visual *
    GetClone(std::function<void(Visual *lhs, Visual *rhs)> copyTo);

protected:
    /************************************************************************/
    /* Mesh Data                                                            */
    /************************************************************************/
    std::shared_ptr<Mesh>                            mMesh;

    /************************************************************************/
    /* Effect Data                                                          */
    /************************************************************************/
    std::list<std::shared_ptr<VisualEffectInstance>> mEffectInstances;
    std::list<std::shared_ptr<VisualEffectParams>>   mEffectParamses;

    // NOTE(Wuxiang): The reason the visual is designed to contains vertex
    // format and vertex group is that if you store them in effect instance you have
    // to deal with the problem of copying effect instance. Because the effect
    // instance is about not sharing passes. Hence you would not be able to copy
    // passes easily. Eventually, you would have problems copying effect instance.
    // This leads to problem that if you make effect instance store vertex format
    // and vertex group you would have trouble copying them as well.
    //
    // By storing them here you could easily reuse mesh and its vertex buffer,
    // vertex format etc. You don't need to worry about coping effect instance
    // also, because you are not allowed to do that.
    std::shared_ptr<const VertexFormat>              mVertexFormat;
    std::shared_ptr<const VertexGroup>               mVertexGroup;
};
#pragma warning(default: 4251)

}
