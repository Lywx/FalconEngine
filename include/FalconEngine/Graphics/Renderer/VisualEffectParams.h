#pragma once

#include <FalconEngine/Core/Macro.h>

namespace FalconEngine
{

// @summary Represents a storage structure for a visual effect parameters. It will
// be later incorporated to editor menu.
FALCON_ENGINE_CLASS_BEGIN VisualEffectParams
{
public:
    virtual ~VisualEffectParams() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    virtual void
    UpdateContext();
};
FALCON_ENGINE_CLASS_END

}
