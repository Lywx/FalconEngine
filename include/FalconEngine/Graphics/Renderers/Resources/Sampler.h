#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

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

class Sampler : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

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

using SamplerSharedPtr = std::shared_ptr<Sampler>;
using SamplerVector = std::vector<const Sampler *>;
using SamplerTable = std::map<int, const Sampler *>;

}
