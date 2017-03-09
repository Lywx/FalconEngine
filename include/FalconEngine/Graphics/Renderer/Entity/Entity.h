#pragma once

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Core/Object.h>

namespace FalconEngine
{

class Entity;
using EntitySharedPtr = std::shared_ptr<Entity>;

class GameEngineInput;

class Node;
using NodeSharedPtr = std::shared_ptr<Node>;

class Visual;
using VisualSharedPtr = std::shared_ptr<Visual>;

class Entity : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit Entity(NodeSharedPtr node);
    virtual ~Entity();

public:
    const NodeSharedPtr
    GetNode() const;

    NodeSharedPtr
    GetNode();

    virtual void
    Update(GameEngineInput *input, double elapsed);

public:
    int         mId;
    std::string mName;

protected:
    NodeSharedPtr mNode;
};

}
