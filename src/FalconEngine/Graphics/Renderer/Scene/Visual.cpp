#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>

#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/Primitive.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Visual, Spatial);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Visual::Visual(const std::shared_ptr<Mesh>& mesh) :
    mMesh(mesh)
{
    // NOTE(Wuxiang): By default Visual "inherit" from Primitives' vertex
    // information. You could override those vertex information by using the
    // setter in Visual API. The vertex format is used in runtime
    // for Visual Effect to check whether the Primitive vertex format is compatible
    // with Visual Effect's shader.
    auto primitive = mesh->GetPrimitive();

    mVertexFormat = primitive->GetVertexFormat();
    mVertexGroup = primitive->GetVertexGroup();
}

Visual::Visual()
{
}

Visual::~Visual()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/

/************************************************************************/
/* Effect Management                                                    */
/************************************************************************/
int
Visual::GetEffectInstanceNum() const
{
    return int(mEffectInstances.size());
}

void
Visual::PushEffectInstance(const std::shared_ptr<VisualEffectInstance>& effectInstance)
{
    FALCON_ENGINE_CHECK_NULLPTR(effectInstance);

    mEffectInstances.push_back(effectInstance);
}

void
Visual::RemoveEffectInstance(const std::shared_ptr<VisualEffectInstance>& effectInstance)
{
    FALCON_ENGINE_CHECK_NULLPTR(effectInstance);

    auto iter = find(mEffectInstances.begin(), mEffectInstances.end(), effectInstance);
    if (iter != mEffectInstances.end())
    {
        mEffectInstances.erase(iter);
    }
}

int
Visual::GetEffectParamsNum() const
{
    return int(mEffectParamses.size());
}

void
Visual::PushEffectParams(const std::shared_ptr<VisualEffectParams>& effectParmas)
{
    FALCON_ENGINE_CHECK_NULLPTR(effectParmas);

    mEffectParamses.push_back(effectParmas);
}

void
Visual::RemoveEffectParams(const std::shared_ptr<VisualEffectParams>& effectParmas)
{
    FALCON_ENGINE_CHECK_NULLPTR(effectParmas);

    auto iter = find(mEffectParamses.begin(), mEffectParamses.end(), effectParmas);
    if (iter != mEffectParamses.end())
    {
        mEffectParamses.erase(iter);
    }
}

const VertexFormat *
Visual::GetVertexFormat() const
{
    return mVertexFormat.get();
}

std::shared_ptr<const VertexFormat>
Visual::GetVertexFormatSp()
{
    return mVertexFormat;
}

void
Visual::SetVertexFormat(const std::shared_ptr<VertexFormat>& vertexFormat)
{
    mVertexFormat = vertexFormat;
}

const VertexGroup *
Visual::GetVertexGroup() const
{
    return mVertexGroup.get();
}

std::shared_ptr<const VertexGroup>
Visual::GetVertexGroupSp()
{
    return mVertexGroup;
}

void
Visual::SetVertexGroup(const std::shared_ptr<VertexGroup>& vertexGroup)
{
    mVertexGroup = vertexGroup;
}

/************************************************************************/
/* Mesh Management                                                      */
/************************************************************************/
const Mesh *
Visual::GetMesh() const
{
    return mMesh.get();
}

Mesh *
Visual::GetMesh()
{
    return mMesh.get();
}

std::shared_ptr<Mesh>
Visual::GetMeshSp()
{
    return mMesh;
}

void
Visual::SetMesh(const std::shared_ptr<Mesh>& mesh)
{
    FALCON_ENGINE_CHECK_NULLPTR(mesh);

    mMesh = mesh;
}

/************************************************************************/
/* Spatial Management                                                   */
/************************************************************************/
void
Visual::UpdateWorldTransform(double elapsed)
{
    Spatial::UpdateWorldTransform(elapsed);
}

/************************************************************************/
/* Deep and Shallow Copy                                                */
/************************************************************************/
void
Visual::CopyTo(Visual *lhs) const
{
    Spatial::CopyTo(lhs);

    lhs->mEffectInstances = mEffectInstances;
    lhs->mEffectParamses = mEffectParamses;
    lhs->mVertexFormat = mVertexFormat;
    lhs->mVertexGroup = mVertexGroup;
    lhs->mMesh = mMesh;
}

Visual *
Visual::GetClone() const
{
    auto clone = new Visual();
    CopyTo(clone);
    return clone;
}

Visual *
Visual::GetClone(std::function<void(Visual *lhs, Visual *rhs)> copyTo)
{
    auto clone = new Visual();
    copyTo(clone, this);
    return clone;
}

}
