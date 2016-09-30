#include <FalconEngine/Graphics/Controllers/ControlledObject.h>

#include <stdexcept>

namespace FalconEngine {

FALCON_ENGINE_IMPLEMENT_RTTI(ControlledObject, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ControlledObject::ControlledObject()
{
}

ControlledObject::~ControlledObject()
{
    DetachAllControllers();
    delete m_Controllers;
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void ControlledObject::AttachController(ControllerPtr controller)
{
    if (!controller)
    {
        throw std::invalid_argument("Cannot attach a null controller\n");
    }

    // Test whether the controller is already in the array.
    int i;
    for (i = 0; i < m_ControllerNum; ++i)
    {
        if (controller == m_Controllers[i])
        {
            return;
        }
    }

    // Bind the controller to the object.
    controller->SetObject(this);

    // The controller is not in the current array, so add it.
    if (m_ControllerNum == m_Capacity)
    {
        // The array is full, so double its capacity.
        m_Capacity *= 2;

        auto *newControllers = new ControllerPtr[m_Capacity];
        for (i = 0; i < m_ControllerNum; ++i)
        {
            newControllers[i] = m_Controllers[i];
        }

        delete m_Controllers;
        m_Controllers = newControllers;
    }

    m_Controllers[m_ControllerNum++] = controller;
}

void ControlledObject::DetachController(ControllerPtr controller)
{
    for (int i = 0; i < m_ControllerNum; ++i)
    {
        if (controller == m_Controllers[i])
        {
            // Unbind the controller from the object.
            controller->SetObject(nullptr);

            // Remove the controller from the array, keeping the array
            // compact.
            for (int j = i + 1; j < m_ControllerNum; ++j, ++i)
            {
                m_Controllers[i] = m_Controllers[j];
            }

            m_Controllers[--m_ControllerNum] = nullptr;
            return;
        }
    }
}

void ControlledObject::DetachAllControllers()
{
    for (int i = 0; i < m_ControllerNum; ++i)
    {
        // Unbind the controller from the object.
        m_Controllers[i]->SetObject(nullptr);
        m_Controllers[i] = nullptr;
    }

    m_ControllerNum = 0;
}

bool ControlledObject::UpdateControllers(double elapsed)
{
    bool updated = false;

    for (int i = 0; i < m_ControllerNum; ++i)
    {
        if (m_Controllers[i]->Update(elapsed))
        {
            updated = true;
        }
    }

    return updated;
}

}
