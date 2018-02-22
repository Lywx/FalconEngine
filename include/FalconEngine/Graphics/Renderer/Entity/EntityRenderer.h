#pragma once

#include <FalconEngine/Core/Macro.h>

#include <vector>
#include <map>
#include <queue>

#include <FalconEngine/Core/Memory.h>
#include <FalconEngine/Math/Color.h>

namespace FalconEngine
{

class Camera;
class Entity;
class Node;
class Primitive;
class Renderer;
class Visual;

FALCON_ENGINE_CLASS_BEGIN EntityRenderer final
{
    FALCON_ENGINE_SINGLETON_SAFE_DECLARE(EntityRenderer);

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
    Draw(const Camera * camera, const Entity * entity);

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
    std::map<const Camera *, std::vector<const Entity *>> mEntityListTable;
};
FALCON_ENGINE_CLASS_END

}
