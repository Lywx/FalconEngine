#pragma once

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Core/Object.h>

namespace FalconEngine
{

class Visual;
using VisualSharedPtr = std::shared_ptr<Visual>;

class Node;
using NodeSharedPtr = std::shared_ptr<Node>;

class Entity : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Entity();
    virtual ~Entity();

public:
    int         mId;
    std::string mName;

protected:
    NodeSharedPtr mNode;
};

}
