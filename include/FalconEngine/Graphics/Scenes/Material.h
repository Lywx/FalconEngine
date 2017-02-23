#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <memory>

namespace FalconEngine
{

class Texture;
class Material : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Material();
    virtual ~Material ();

    void
    SetAmbient(const Texture *texture)
    {
        mAmbient = texture;
    }

    const Texture *
    GetAmbient() const
    {
        return mAmbient;
    }

    void
    SetDiffuse(const Texture *texture)
    {
        mDiffuse = texture;
    }

    const Texture *
    GetDiffuse() const
    {
        return mDiffuse;
    }

    void
    SetEmissive(const Texture *texture)
    {
        mEmissive = texture;
    }

    const Texture *
    GetEmissive() const
    {
        return mEmissive;
    }

    void
    SetSpecular(const Texture *texture)
    {
        mSpecular = texture;
    }

    const Texture *
    GetSpecular() const
    {
        return mSpecular;
    }

private:
    const Texture *mAmbient;
    const Texture *mDiffuse;
    const Texture *mEmissive;
    const Texture *mSpecular;
};

using MaterialSharedPtr = std::shared_ptr<Material>;

}
