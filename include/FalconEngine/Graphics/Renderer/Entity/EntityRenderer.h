#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <vector>
#include <map>
#include <queue>

namespace FalconEngine
{

class BoundingBox;
class Camera;
class Entity;
class Node;
class Renderer;
class Visual;

#if defined(FALCON_ENGINE_PLATFORM_QT)
#include <QtGui/QOpenGLFunctions>
class EntityRenderer sealed : QOpenGLFunctions
#else
class EntityRenderer sealed
#endif
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    EntityRenderer();
    virtual ~EntityRenderer();

public:
    /************************************************************************/
    /* Rendering API                                                        */
    /************************************************************************/
    void
    Draw(const Camera *camera, const Entity *entity);

    void
    DrawBoundingBox(const Camera *camera, const BoundingBox *boundingBox);

    void
    DrawBoundingBox(const Camera *camera, const Entity *entity);

    void
    DrawBoundingBox(const Camera *camera, const Node *node);

    void
    DrawBoundingBox(const Camera *camera, const Visual *visual);

    /************************************************************************/
    /* Rendering Engine API                                                 */
    /************************************************************************/
    void
    Initialize();

    void
    RenderBegin();

    void
    Render(Renderer *renderer, double percent);

    void
    RenderEnd();

private:
    using BoundingBoxVectorMap = std::map<const Camera *, std::vector<const BoundingBox *>>;
    using EntityVectorMap = std::map<const Camera *, std::vector<const Entity *>>;
    using NodeQueue = std::queue<std::pair<Node *, int>>;

    BoundingBoxVectorMap mBoundingBoxRenderTable;
    EntityVectorMap      mEntityRenderTable;

    NodeQueue            mNodeRenderQueueCurrent;
    NodeQueue            mNodeRenderQueueNext;
};

}
