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

FALCON_ENGINE_CLASS_BEGIN Sampler
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
    SamplerMinificationFilter mMinificationFilter;
    bool mMipmapEnabled;
    SamplerMipmapFilter mMipmapFilter;
    SamplerWrapMode mWrapS;
    SamplerWrapMode mWrapT;
    SamplerWrapMode mWrapR;
};
FALCON_ENGINE_CLASS_END

FALCON_ENGINE_CLASS_BEGIN SamplerAttachment
{
public:
    SamplerAttachment() :
        mSampler(nullptr),
        mShaderMask(0)
    {
    }

    SamplerAttachment(const Sampler * sampler, unsigned int shaderMask) :
        mSampler(sampler),
        mShaderMask(shaderMask)
    {
    }

public:
    const Sampler *mSampler;
    unsigned int mShaderMask;
};
FALCON_ENGINE_CLASS_END

}
