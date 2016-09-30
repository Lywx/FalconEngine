#include <FalconEngine/Core/Objects/Rtti.h>

namespace FalconEngine {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Rtti::Rtti (const char *name, const Rtti *baseType)
{
    m_Name = name;
    m_BaseType = baseType;
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

        search = search->m_BaseType;
    }

    return false;
}

}