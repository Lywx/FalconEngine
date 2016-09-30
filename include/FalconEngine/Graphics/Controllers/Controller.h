#pragma once

#include <memory>

#include <FalconEngine/Core/Objects/Object.h>

namespace FalconEngine {

class ControlledObject;
class Controller : public Object
{
    FALCON_ENGINE_DECLARE_RTTI;

protected:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    // Abstract base class. Construction and destruction.
    Controller();

public:
    virtual ~Controller();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    inline ControlledObject *GetObject() const;

    // This function is public because the class ControlledObject needs to set
    // the object during a call to AttachController. Derived classes that
    // manage a set of controllers also need to set the objects during a call
    // to AttachController.
    virtual void SetObject(ControlledObject *object);

    virtual bool Update(double elapsed);

    bool Active = true;

protected:
    // The controlled object. This is a regular pointer rather than a
    // smart pointer to avoid the reference cycle between m_Object and
    // 'this'.
    ControlledObject *m_Object = nullptr;
};

typedef std::shared_ptr<Controller> ControllerPtr;
#include "Controller.inl"

}
