#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <list>
#include <vector>

#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderMessage.h>

namespace FalconEngine
{

class DebugRenderMessageManager
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    DebugRenderMessageManager() = default;
    ~DebugRenderMessageManager() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    UpdateFrame(double elapsed);

public:
    std::list<DebugRenderMessage> mMessageList;
};

}
