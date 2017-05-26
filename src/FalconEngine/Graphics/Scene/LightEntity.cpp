#include <FalconEngine/Graphics/Scene/LightEntity.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(LightEntity, Entity);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
LightEntity::LightEntity(const std::shared_ptr<Node> node, LightType lightType) :
    SceneEntity(node),
    mLight(std::make_shared<Light>(lightType))
{
    using namespace std::placeholders;

    mNode->mUpdateEnded += &mNodeUpdateEndedHandler;

    // NOTE(Wuxiang): The light indicator model is 1 * 1 meter. It is too big for
    // an indicator.
    SetScale(Vector3f(0.25f, 0.25f, 0.25f));
}

LightEntity::LightEntity(const std::shared_ptr<Node> node, const std::shared_ptr<Light> light) :
    SceneEntity(node),
    mLight(light)
{
}

LightEntity::~LightEntity()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
Color
LightEntity::GetAmbient() const
{
    return mLight->mAmbient;
}

void
LightEntity::SetAmbient(Color color)
{
    mLight->mAmbient = color;
}

Color
LightEntity::GetDiffuse() const
{
    return mLight->mDiffuse;
}

void
LightEntity::SetDiffuse(Color color)
{
    mLight->mDiffuse = color;
}

Color
LightEntity::GetSpecular() const
{
    return mLight->mSpecular;
}

void
LightEntity::SetSpecular(Color color)
{
    mLight->mSpecular = color;
}

float
LightEntity::GetConstant() const
{
    return mLight->mConstant;
}

void
LightEntity::SetConstant(float value)
{
    mLight->mConstant = value;
}

float
LightEntity::GetLinear() const
{
    return mLight->mLinear;
}

void
LightEntity::SetLinear(float value)
{
    mLight->mLinear = value;
}

float
LightEntity::GetQuadratic() const
{
    return mLight->mQuadratic;
}

void
LightEntity::SetQuadratic(float value)
{
    mLight->mQuadratic = value;
}

Vector3f
LightEntity::GetDirection() const
{
    return mLight->mDirection;
}

void
LightEntity::SetDirection(Vector3f direciton)
{
    mLight->mDirection = direciton;
}

const Light *
LightEntity::GetLight() const
{
    return mLight.get();
}

std::shared_ptr<Light>
LightEntity::GetLight()
{
    return mLight;
}

void
LightEntity::UpdateLocalTransformFeedback(bool /* initiator */)
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
