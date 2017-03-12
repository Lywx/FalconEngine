#include <FalconEngine/Graphics/Scene/PointLightEntity.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(PointLightEntity, Entity);

PointLightEntity::PointLightEntity(const NodeSharedPtr node) :
    Entity(node),
    mLight(std::make_shared<Light>(LightType::Point))
{
    using namespace std::placeholders;

    //EventBinder<bool> a  = std::bind(&PointLightEntity::UpdateLightLocalTransform, this, _1);
    //mNodeUpdateEndHandler = a;
    mNode->mUpdateEnded += &mNodeUpdateEndedHandler;

    // NOTE(Wuxiang): The light indicator model is 1 * 1 meter. It is too big for
    // an indicator.
    SetScale(Vector3f(0.25f, 0.25f, 0.25f));
}

PointLightEntity::PointLightEntity(const NodeSharedPtr node, const LightSharedPtr light) :
    Entity(node),
    mLight(light)
{
}

PointLightEntity::~PointLightEntity()
{
}

Color
PointLightEntity::GetAmbient() const
{
    return mLight->mAmbient;
}

void
PointLightEntity::SetAmbient(Color color)
{
    mLight->mAmbient = color;
}

Color
PointLightEntity::GetDiffuse() const
{
    return mLight->mDiffuse;
}

void
PointLightEntity::SetDiffuse(Color color)
{
    mLight->mDiffuse = color;
}

Color
PointLightEntity::GetSpecular() const
{
    return mLight->mSpecular;
}

void
PointLightEntity::SetSpecular(Color color)
{
    mLight->mSpecular = color;
}

float
PointLightEntity::GetConstant() const
{
    return mLight->mConstant;
}

void
PointLightEntity::SetConstant(float value)
{
    mLight->mConstant = value;
}

float
PointLightEntity::GetLinear() const
{
    return mLight->mLinear;
}

void
PointLightEntity::SetLinear(float value)
{
    mLight->mLinear = value;
}

float
PointLightEntity::GetQuadratic() const
{
    return mLight->mQuadratic;
}

void
PointLightEntity::SetQuadratic(float value)
{
    mLight->mQuadratic = value;
}

const Light *
PointLightEntity::GetLight() const
{
    return mLight.get();
}

void
PointLightEntity::UpdateLocalTransformFeedback(bool initiator)
{
    if (mNode->mWorldTransformIsCurrent)
    {
        mLight->mPosition = Vector3f(mNode->mWorldTransform * Vector4f(0, 0, 0, 1));
    }
    else
    {
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }
}

}
