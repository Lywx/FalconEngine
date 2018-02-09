#pragma once

#include <FalconEngine/Core/Macro.h>

namespace FalconEngine
{

// @remark RTTI provide more functionality than C++ built-in RTTI.
FALCON_ENGINE_CLASS_BEGIN Rtti
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Rtti(const char *name, const Rtti * baseType);
    ~Rtti();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    inline const char *
    GetName() const;

    inline bool
    IsExactly(const Rtti & type) const;

    bool
    IsDerived(const Rtti & type) const;

private:
    const char *mTypeName;
    const Rtti *mTypeBase;
};
FALCON_ENGINE_CLASS_END

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
    static const Rtti sRttiType; \
    \
    virtual const Rtti& GetDynamicType() const override;

#define FALCON_ENGINE_RTTI_IMPLEMENT(Klass, BaseKlass) \
    const Rtti Klass::sRttiType(#Klass, &BaseKlass::sRttiType); \
    \
    const Rtti& Klass::GetDynamicType() const \
    { \
        return sRttiType; \
    }