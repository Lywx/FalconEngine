#pragma once

#include <FalconEngine/GraphicsInclude.h>
#include <vector>

namespace FalconEngine
{

class Entity;

class Renderer;

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
    Draw(const Entity *entity);

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
    std::vector<const Entity *> mEntityList;
};

}
