#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <vector>
#include <map>
#include <queue>

#include <FalconEngine/Math/Color.h>

namespace FalconEngine
{

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
#pragma warning(default: 4251)

}
