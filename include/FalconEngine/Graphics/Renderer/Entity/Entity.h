#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <FalconEngine/Core/EventHandler.h>
#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

class Entity;

class GameEngineInput;

class Node;

class Visual;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API Entity : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit Entity(std::shared_ptr<Node> node);
    virtual ~Entity();

public:
    const Node *
    GetNode() const;

    std::shared_ptr<Node>
    GetNode();

    virtual Vector3f
    GetScale() const;

    void
    SetScale(Vector3f scale);

    Vector3f
    GetPosition() const;

    void
    SetPosition(Vector3f position);

    virtual void
    Update(GameEngineInput *input, double elapsed);

protected:
    virtual void
    UpdateLocalTransform(bool initiator);

    virtual void
    UpdateLocalTransformFeedback(bool initiator);

public:
    // NEW(Wuxiang): Id is not implemented.
    int         mId;
    std::string mName;

protected:
    std::shared_ptr<Node> mNode;
    EventCallback<bool>   mNodeUpdateBegunHandler;
    EventCallback<bool>   mNodeUpdateEndedHandler;

    // NOTE(Wuxiang): Note that all transform data is local to parent node.
    Vector3f      mLocalPosition;
    Vector3f      mLocalScale;
    bool          mLocalTransformIsCurrent;
};
#pragma warning(default: 4251)

}
