#pragma once

namespace FalconEngine
{

class Rtti
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Rtti (const char *name, const Rtti *baseType);
    ~Rtti ();

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
    static const Rtti Type; \
    \
    virtual const Rtti& GetType() const \
    { \
        return Type; \
    }

#define FALCON_ENGINE_RTTI_IMPLEMENT(klass, baseklass) \
    const Rtti klass::Type(#klass, &baseklass::Type)
