#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>

namespace FalconEngine
{

class Renderer;
class VertexFormat;

class FALCON_ENGINE_API PlatformVertexFormat final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformVertexFormat(Renderer *, const VertexFormat *vertexFormat);
    ~PlatformVertexFormat();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(Renderer *renderer);

    void
    Disable(Renderer *renderer);

    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
private:
    void
    CreateInputLayout(ID3D11Device4 *device);

private:
    ID3D11InputLayout  *mInputLayout;
    const VertexFormat *mVertexFormat;
};
}

#endif