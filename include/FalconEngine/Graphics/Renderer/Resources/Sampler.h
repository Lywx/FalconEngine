#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <map>
#include <vector>

namespace FalconEngine
{

enum class SamplerMinificationFilter
{
    Nearest,
    Linear,

    NearestMipmapNearest,
    NearestMipmapLinear,
    LinearMipmapNearest,
    LinearMipmapLinear,

    Count,
};

enum class SamplerMagnificationFilter
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

class Sampler
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