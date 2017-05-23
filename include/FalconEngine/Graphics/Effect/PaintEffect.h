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
class FALCON_ENGINE_API PaintEffect : public VisualEffect
{
    //  FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PaintEffect();
    virtual ~PaintEffect();
};
#pragma warning(default: 4251)

}
