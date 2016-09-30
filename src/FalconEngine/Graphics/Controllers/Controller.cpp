#include <FalconEngine/Graphics/Controllers/Controller.h>

namespace FalconEngine {

FALCON_ENGINE_IMPLEMENT_RTTI(Controller, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Controller::Controller()
{
}

Controller::~Controller()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void Controller::SetObject(ControlledObject *object)
{
    m_Object = object;
}

bool Controller::Update(double elapsed)
{
    if (Active)
    {
        return true;
    }

    return false;
}

}
