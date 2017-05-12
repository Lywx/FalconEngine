#pragma once

#include <FalconEngine/Core/Macro.h>

namespace FalconEngine
{

class FALCON_ENGINE_ITEM_CORE Rtti
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Rtti(const char *name, const Rtti *baseType);
    ~Rtti();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    inline const char *
    GetName() const;

    inline bool
    IsExactly(const Rtti& type) const;

    bool
    IsDerived(const Rtti& type) const;

private:
    const char *mTypeName;
    const Rtti *mTypeBase;
};

const char *
Rtti::GetName() const
{
    return mTypeName;
}

bool
Rtti::IsExactly(const Rtti& type) const
{
    return &type == this;
}

}

#define FALCON_ENGINE_RTTI_DECLARE \
public: \
    static const Rtti sType; \
    \
    virtual const Rtti& GetType() const;

#define FALCON_ENGINE_RTTI_DECLARE_EXPORT(klass) \
    FALCON_ENGINE_ITEM_CORE const Rtti& klass##sType();

#define FALCON_ENGINE_RTTI_IMPLEMENT(klass, baseklass) \
    const Rtti klass::sType(#klass, &baseklass##sType()); \
    \
    const Rtti& klass::GetType() const \
    { \
        return sType; \
    }

#define FALCON_ENGINE_RTTI_IMPLEMENT_EXPORT(klass) \
    const Rtti& klass##sType() \
    { \
        return klass::sType; \
    }
