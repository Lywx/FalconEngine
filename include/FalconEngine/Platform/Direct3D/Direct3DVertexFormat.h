#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>

namespace FalconEngine
{

class Renderer;
class VertexFormat;

FALCON_ENGINE_CLASS_BEGIN PlatformVertexFormat final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformVertexFormat(Renderer *, const VertexFormat * vertexFormat);
    ~PlatformVertexFormat();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(Renderer * renderer);

    void
    Disable(Renderer * renderer);

    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
private:
    void
    CreateInputLayout(ID3D11Device1 * device);

private:
    Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;
    const VertexFormat *mVertexFormat;
};
FALCON_ENGINE_CLASS_END

}

#endif