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
    static const Rtti sType;

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
    GetType() const;

    bool
    IsExactly(const Rtti& type) const;

    bool
    IsExactlyTypeOf(const Object *object) const;

    bool
    IsDerived(const Rtti& type) const;

    bool
    IsDerivedTypeOf(const Object *object) const;
};

}
