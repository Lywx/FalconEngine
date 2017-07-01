#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>

#include <FalconEngine/Graphics/Renderer/Scene/Node.h>
#include <FalconEngine/Math/Matrix4.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Entity, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Entity::Entity(std::shared_ptr<Node> node) :
    mId(0),
    mNode(node),
    mLocalPosition(),
    mLocalScale(Vector3f(1, 1, 1)),
    mLocalTransformIsCurrent(true)
{
    using namespace std::placeholders;

    mNodeUpdateBegunHandler = EventBinder<bool>(std::bind(&Entity::UpdateLocalTransform, this, _2));
    mNodeUpdateEndedHandler = EventBinder<bool>(std::bind(&Entity::UpdateLocalTransformFeedback, this, _2));

    mNode->mUpdateBegun += &mNodeUpdateBegunHandler;
    mNode->mUpdateEnded += &mNodeUpdateEndedHandler;
}

Entity::~Entity()
{
    mNode->mUpdateBegun -= &mNodeUpdateBegunHandler;
    mNode->mUpdateEnded -= &mNodeUpdateEndedHandler;
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const Node *
Entity::GetNode() const
{
    return mNode.get();
}

std::shared_ptr<Node>
Entity::GetNode()
{
    return mNode;
}

Vector3f
Entity::GetScale() const
{
    return mLocalScale;
}

void
Entity::SetScale(Vector3f scale)
{
    mLocalScale = scale;
    mLocalTransformIsCurrent = false;
}

Vector3f
Entity::GetPosition() const
{
    return mLocalPosition;
}

void
Entity::SetPosition(Vector3f position)
{
    mLocalPosition = position;
    mLocalTransformIsCurrent = false;
}

void
Entity::Update(GameEngineInput * /* input */, double /* elapsed */)
{
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
Entity::UpdateLocalTransform(bool /* initiator */)
{
    if (!mLocalTransformIsCurrent)
    {
        mNode->mLocalTransform = Matrix4f::CreateTranslation(mLocalPosition) * Matrix4f::CreateScale(mLocalScale.x, mLocalScale.y, mLocalScale.z);
        mNode->mWorldTransformIsCurrent = false;

        mLocalTransformIsCurrent = true;
    }
}

void
Entity::UpdateLocalTransformFeedback(bool /* initiator */)
{
}

}
