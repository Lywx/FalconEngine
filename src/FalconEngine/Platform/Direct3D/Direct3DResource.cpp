#include <FalconEngine/Platform/Direct3D/Direct3DResource.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformResource::PlatformResource(Renderer *renderer) :
    mCpuFlag(0),
    mMiscFlags(0),
    mUsage(D3D11_USAGE_DEFAULT),
    mRenderTargetView(nullptr),
    mShaderResourceView(nullptr),
    mUnorderedAccessView(nullptr)
{
}

PlatformResource::~PlatformResource()
{
}

}

#endif