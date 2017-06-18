#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <vector>
#include <map>
#include <queue>

#include <FalconEngine/Graphics/Renderer/Entity/AABBBoundingBoxBatch.h>

#include <FalconEngine/Math/Color.h>

namespace FalconEngine
{

class BoundingBox;

class Camera;
class Entity;
class Node;
class Primitive;
class Renderer;
class Visual;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API EntityRenderer final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    EntityRenderer();
    ~EntityRenderer();

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

    std::shared_ptr<AABBBoundingBoxBatch>
    PrepareBatch(const Camera *camera);

    void
    PrepareBoundingBox(_IN_ AABBBoundingBoxBatch&  batch,
                       _IN_ const Camera      *camera,
                       _IN_ const Visual      *visual,
                       _IN_ const BoundingBox *boundingBox,
                       _IN_ Color              boundingBoxColor = ColorPalette::White);
private:
    std::map<const Camera *, std::shared_ptr<AABBBoundingBoxBatch>> mBoundingBoxBatchTable;
    std::map<const Camera *, std::vector<const Entity *>>       mEntityListTable;
};
#pragma warning(default: 4251)

}
