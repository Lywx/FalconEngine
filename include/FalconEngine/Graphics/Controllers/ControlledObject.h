#pragma once

#include <stdexcept>

#include <FalconEngine/Core/Objects/Object.h>
#include <FalconEngine/Graphics/Controllers/Controller.h>

namespace FalconEngine {

class ControlledObject : public Object
{
    FALCON_ENGINE_DECLARE_RTTI;

protected:
    // Abstract base class
    ControlledObject();

public:
    virtual ~ControlledObject();

    inline int           GetControllerNum() const;
    inline ControllerPtr GetController(int i) const;

    void AttachController(ControllerPtr controller);
    void DetachController(ControllerPtr controller);
    void DetachAllControllers();

    bool UpdateControllers(double elapsed);

private:
    int m_ControllerNum = 0;
    int m_Capacity = 0;
    ControllerPtr *m_Controllers = nullptr;
};

#include "ControlledObject.inl"
}
