#include <FalconEngine/Core/Object.h>

namespace FalconEngine
{

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
const Rtti Object::sType("Object", nullptr);

const Rtti&
Object::GetType() const
{
    return sType;
}

const Rtti&
ObjectsType()
{
    return Object::sType;
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Object::~Object()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
bool
Object::IsExactly(const Rtti& type) const
{
    return GetType().IsExactly(type);
}

bool
Object::IsExactlyTypeOf(const Object *object) const
{
    return object && GetType().IsExactly(object->GetType());
}

bool
Object::IsDerived(const Rtti& type) const
{
    return GetType().IsDerived(type);
}

bool
Object::IsDerivedTypeOf(const Object *object) const
{
    return object && GetType().IsDerived(object->GetType());
}
}
