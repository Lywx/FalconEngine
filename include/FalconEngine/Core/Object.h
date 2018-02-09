#pragma once

#include <FalconEngine/Core/Macro.h>
#include <FalconEngine/Core/Rtti.h>

namespace FalconEngine
{

class FALCON_ENGINE_API Object
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static const Rtti sRttiType;

    static const Rtti&
    GetStaticType();

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    virtual ~Object();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    virtual const Rtti&
    GetDynamicType() const;

    bool
    IsExactly(const Rtti& type) const;

    bool
    IsDerived(const Rtti& type) const;

    bool
    HasSameType(const Object *object) const;

    bool
    HasDerivedType(const Object *object) const;
};

}
