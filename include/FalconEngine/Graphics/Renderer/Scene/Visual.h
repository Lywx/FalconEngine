#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <functional>

#include <FalconEngine/Graphics/Renderer/Scene/Mesh.h>
#include <FalconEngine/Graphics/Renderer/Scene/Spatial.h>

namespace FalconEngine
{

class BoundingBox;

class Primitive;

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
    explicit Visual(std::shared_ptr<Mesh> mesh);
    Visual(std::shared_ptr<Mesh> mesh,
           std::shared_ptr<VertexFormat> vertexFormat,
           std::shared_ptr<VertexGroup> vertexGroup);

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
    const VisualEffectInstance *
    GetInstance() const;

    std::shared_ptr<VisualEffectInstance>
    GetInstance();

    void
    SetInstance(std::shared_ptr<VisualEffectInstance> effectInstance);

    const VertexFormat *
    GetVertexFormat() const;

    std::shared_ptr<VertexFormat>
    GetVertexFormat();

    void
    SetVertexFormat(std::shared_ptr<VertexFormat> vertexFormat);

    const VertexGroup *
    GetVertexGroup() const;

    std::shared_ptr<VertexGroup>
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
    std::shared_ptr<Mesh>                 mMesh;

    /************************************************************************/
    /* Effect Data                                                          */
    /************************************************************************/
    std::shared_ptr<VisualEffectInstance> mInstance;
    std::shared_ptr<VertexFormat>         mVertexFormat;
    std::shared_ptr<VertexGroup>          mVertexGroup;

};
#pragma warning(default: 4251)

}
