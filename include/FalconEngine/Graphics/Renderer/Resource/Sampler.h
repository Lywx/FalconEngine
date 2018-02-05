#pragma once

#include <FalconEngine/Core/Macro.h>

#include <map>
#include <vector>

namespace FalconEngine
{

enum class SamplerMagnificationFilter
{
    Nearest,
    Linear,

    Count,
};

enum class SamplerMinificationFilter
{
    Nearest,
    Linear,

    Count,
};

enum class SamplerMipmapFilter
{
    Nearest,
    Linear,

    Count,
};

enum class SamplerWrapMode
{
    ClampToBorder,
    ClampToEdge,
    Repeat,
    RepeatMirrored,

    Count,
};

class FALCON_ENGINE_API Sampler
{
public:
    Sampler();
    Sampler(SamplerMagnificationFilter magnificationFilter,
            SamplerMinificationFilter minificationFilter,
            SamplerMipmapFilter mipmapFilter,
            SamplerWrapMode wrapS,
            SamplerWrapMode wrapT,
            SamplerWrapMode wrapR);

    virtual ~Sampler();

public:
    SamplerMagnificationFilter mMagnificationFilter;
    SamplerMinificationFilter  mMinificationFilter;
    bool                       mMipmapEnabled;
    SamplerMipmapFilter        mMipmapFilter;
    SamplerWrapMode            mWrapS;
    SamplerWrapMode            mWrapT;
    SamplerWrapMode            mWrapR;
};

}
