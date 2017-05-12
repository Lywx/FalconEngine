#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <functional>
#include <queue>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>

namespace FalconEngine
{

class Visual;
class Mesh;
class Node;

#pragma warning(disable: 4251)
class FALCON_ENGINE_ITEM_GRAPHICS MeshEffect : public VisualEffect
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    MeshEffect();
    virtual ~MeshEffect();

protected:
    void
    TraverseLevelOrder(Node *meshRoot, std::function<void(Mesh *)> meshOperation);

private:
    using NodeQueue = std::queue<std::pair<Node *, int>>;

    NodeQueue mNodeQueueCurrent;
    NodeQueue mNodeQueueNext;
};
#pragma warning(default: 4251)

}
