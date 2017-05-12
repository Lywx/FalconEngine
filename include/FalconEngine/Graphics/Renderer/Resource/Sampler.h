#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <map>
#include <vector>

namespace FalconEngine
{

enum class FALCON_ENGINE_ITEM_GRAPHICS SamplerMinificationFilter
{
    Nearest,
    Linear,

    NearestMipmapNearest,
    NearestMipmapLinear,
    LinearMipmapNearest,
    LinearMipmapLinear,

    Count,
};

enum class FALCON_ENGINE_ITEM_GRAPHICS SamplerMagnificationFilter
{
    Nearest,
    Linear,

    Count,
};

enum class FALCON_ENGINE_ITEM_GRAPHICS SamplerWrapMode
{
    ClampToBorder,
    ClampToEdge,
    Repeat,
    RepeatMirrored,

    Count,
};

class FALCON_ENGINE_ITEM_GRAPHICS Sampler
{
public:
    Sampler();
    Sampler(SamplerMinificationFilter minificationFilter,
            SamplerMagnificationFilter magnificationFilter,
            SamplerWrapMode wrapS,
            SamplerWrapMode wrapT,
            SamplerWrapMode wrapR);

    virtual ~Sampler();

public:
    SamplerMinificationFilter  mMinificationFilter;
    SamplerMagnificationFilter mMagnificationFilter;
    SamplerWrapMode            mWrapS;
    SamplerWrapMode            mWrapT;
    SamplerWrapMode            mWrapR;
};

}
