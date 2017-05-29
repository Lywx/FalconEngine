#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>

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
Visual::Visual(std::shared_ptr<Mesh> mesh) :
    mMesh(mesh),
    mVertexFormat(mesh->GetPrimitive()->GetVertexFormat()),
    mVertexGroup(mesh->GetPrimitive()->GetVertexGroup())
{
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
Visual::PushEffectInstance(std::shared_ptr<VisualEffectInstance> effectInstance)
{
    // NOTE(Wuxiang): Don't allow
    FALCON_ENGINE_CHECK_NULLPTR(effectInstance);

    mEffectInstances.push_back(effectInstance);
}

void
Visual::RemoveEffectInstance(std::shared_ptr<VisualEffectInstance> effectInstance)
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
Visual::PushEffectParams(std::shared_ptr<VisualEffectParams> effectParmas)
{
    FALCON_ENGINE_CHECK_NULLPTR(effectParmas);

    mEffectParamses.push_back(effectParmas);
}

void
Visual::RemoveEffectParams(std::shared_ptr<VisualEffectParams> effectParmas)
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

std::shared_ptr<VertexFormat>
Visual::GetVertexFormat()
{
    return mVertexFormat;
}

void
Visual::SetVertexFormat(std::shared_ptr<VertexFormat> vertexFormat)
{
    mVertexFormat = vertexFormat;
}

const VertexGroup *
Visual::GetVertexGroup() const
{
    return mVertexGroup.get();
}

std::shared_ptr<VertexGroup>
Visual::GetVertexGroup()
{
    return mVertexGroup;
}

void
Visual::SetVertexGroup(std::shared_ptr<VertexGroup> vertexGroup)
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

std::shared_ptr<Mesh>
Visual::GetMesh()
{
    return mMesh;
}

void
Visual::SetMesh(std::shared_ptr<Mesh> mesh)
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
