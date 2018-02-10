#pragma once

#include <memory>

#include <FalconEngine/Core/Macro.h>
#include <FalconEngine/Core/EventHandler.h>
#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

class Entity;

class GameEngineInput;

class Node;

class Visual;

FALCON_ENGINE_CLASS_BEGIN Entity :
public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit Entity(const std::shared_ptr<Node>& node);
    virtual ~Entity();

public:
    const Node *
    GetNode() const;

    Node *
    GetNode();

    std::shared_ptr<Node>
    GetNodeSp();

    virtual Vector3f
    GetScale() const;

    void
    SetScale(Vector3f scale);

    Vector3f
    GetPosition() const;

    void
    SetPosition(Vector3f position);

    virtual void
    Update(GameEngineInput * input, double elapsed);

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
FALCON_ENGINE_CLASS_END

}
