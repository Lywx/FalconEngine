#include <FalconEngine/Core/Rtti.h>

namespace FalconEngine {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Rtti::Rtti (const char *name, const Rtti *baseType)
{
    mTypeName = name;
    mTypeBase = baseType;
}

Rtti::~Rtti ()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
bool Rtti::IsDerived (const Rtti& type) const
{
    const auto *search = this;

    // Linear search
    while (search)
    {
        if (search == &type)
        {
            return true;
        }

        search = search->mTypeBase;
    }

    return false;
}

}