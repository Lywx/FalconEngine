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

class TextureSampler : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    TextureSampler();
    TextureSampler(SamplerMinificationFilter minificationFilter,
                   SamplerMagnificationFilter magnificationFilter,
                   SamplerWrapMode wrapS,
                   SamplerWrapMode wrapT,
                   SamplerWrapMode wrapR);

    virtual ~TextureSampler();

public:
    SamplerMinificationFilter  mMinificationFilter;
    SamplerMagnificationFilter mMagnificationFilter;
    SamplerWrapMode            mWrapS;
    SamplerWrapMode            mWrapT;
    SamplerWrapMode            mWrapR;
};

typedef std::vector<TextureSampler *> TextureSamplerVector;
typedef std::map<int, TextureSampler *> TextureSamplerTable;

}
