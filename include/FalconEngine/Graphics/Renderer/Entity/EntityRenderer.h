#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <vector>
#include <map>
#include <queue>

#include <FalconEngine/Graphics/Renderer/Entity/BoundingBoxBatch.h>

#include <FalconEngine/Math/Color.h>

namespace FalconEngine
{

class BoundingBox;
using BoundingBoxBatchSharedPtr = std::shared_ptr<BoundingBoxBatch>;

class Camera;
class Entity;
class Node;
class Primitive;
class Renderer;
class Visual;

#pragma warning(disable: 4251)
#if defined(FALCON_ENGINE_WINDOW_QT)
#include <QtGui/QOpenGLFunctions>
class FALCON_ENGINE_API EntityRenderer final : QOpenGLFunctions
#elif defined(FALCON_ENGINE_WINDOW_GLFW)
class FALCON_ENGINE_API EntityRenderer final
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
    DrawBoundingBox(const Camera *camera, const Entity *entity, Color boundingBoxColor);

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
    void
    DrawBoundingBox(const Camera *camera, const Node *node, Color boundingBoxColor);

    void
    DrawBoundingBox(const Camera *camera, const Visual *visual, Color boundingBoxColor);

    void
    DrawBoundingBox(const Camera *camera, const Visual *visual, const BoundingBox *boundingBox, Color boundingBoxColor);

    BoundingBoxBatchSharedPtr
    PrepareBatch(const Camera *camera);

    void
    PrepareBoundingBox(_IN_ BoundingBoxBatch&  batch,
                       _IN_ const Camera      *camera,
                       _IN_ const Visual      *visual,
                       _IN_ const BoundingBox *boundingBox,
                       _IN_ Color              boundingBoxColor = ColorPalette::White);
private:
    using EntityVectorMap = std::map<const Camera *, std::vector<const Entity *>>;
    using NodeQueue = std::queue<std::pair<Node *, int>>;

    using BoundingBoxBatchMap = std::map<const Camera *, BoundingBoxBatchSharedPtr>;

    BoundingBoxBatchMap mEntityBoundingBoxBatchTable;
    EntityVectorMap     mEntityTable;

    NodeQueue           mNodeQueueCurrent;
    NodeQueue           mNodeQueueNext;
};
#pragma warning(default: 4251)

}
