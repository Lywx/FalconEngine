#pragma once

#include <FalconEngine/Core/Macro.h>

#include <string>
#include <unordered_map>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN ShaderMetadata final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    ShaderMetadata();
    ~ShaderMetadata() = default;

public:
    // NEW(Wuxiang): Add OpenGL query like GL_MAX_UNIFORM_BUFFER_BINDINGS, etc
    // (sampler, texture, uniform buffer etc) to check in runtime validity of binding
    // index or texture unit.
};
FALCON_ENGINE_CLASS_END

}
