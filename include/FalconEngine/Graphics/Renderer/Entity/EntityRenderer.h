#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <vector>
#include <map>
#include <queue>

#include <FalconEngine/Graphics/Renderer/Entity/EntityAABBBatch.h>

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
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
public:
    static EntityRenderer *
    GetInstance()
    {
        static EntityRenderer sInstance;
        return &sInstance;
    }

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
private:
    EntityRenderer();

public:
    ~EntityRenderer();

public:
    /************************************************************************/
    /* Rendering API                                                        */
    /************************************************************************/
    void
    Draw(const Camera *camera, const Entity *entity);

    // @summary Recursively draw bounding box for the entity.
    void
    DrawBoundingBox(const Camera *camera, const Entity *entity, const Color& color);

    // @summary Recursively draw bounding box for the node.
    void
    DrawBoundingBox(const Camera *camera, const Node *node, const Color& color);

    /************************************************************************/
    /* Rendering Engine API                                                 */
    /************************************************************************/
    void
    Initialize();

    void
    RenderBegin();

    void
    Render(double percent);

    void
    RenderEnd();

private:
    void
    DrawBoundingBox(const Camera *camera, const Visual *visual, const Color& color);

    std::shared_ptr<EntityAABBBatch>
    FindBoundingBoxBatch(const Camera *camera);

    void
    FillBoundingBox(_IN_ EntityAABBBatch& batch,
                    _IN_ const Camera    *camera,
                    _IN_ const Visual    *visual,
                    _IN_ Color            color = ColorPalette::White);
private:
    std::map<const Camera *, std::vector<const Entity *>>      mEntityListTable;
    std::map<const Camera *, std::shared_ptr<EntityAABBBatch>> mEntityAABBBatchTable;

};
#pragma warning(default: 4251)

}
