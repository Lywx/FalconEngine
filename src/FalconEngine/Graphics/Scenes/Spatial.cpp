#include <FalconEngine/Graphics/Scenes/Spatial.h>

namespace FalconEngine
{

FALCON_ENGINE_IMPLEMENT_RTTI(Spatial, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/

Spatial::Spatial() :
    m_worldTransformIsCurrent(false),
    m_parent(nullptr)
{
}

Spatial::~Spatial()
{
    // The Parent member is not reference counted by Spatial, so do not
    // release it here. The memory management responsibility belongs to
    // the owner of each Spatial object.
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/

void Spatial::Update(double elaped, bool initiator)
{
    // Update spatial owned data
    UpdateWorldTransform(elaped);

    if (initiator)
    {
    }
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/

void Spatial::UpdateWorldTransform(double elaped)
{
    // Update world transforms.
    if (!m_worldTransformIsCurrent)
    {
        if (m_parent)
        {
            m_worldTransform = m_parent->m_worldTransform * m_localTransform;
        }
        else
        {
            m_worldTransform = m_localTransform;
        }

        m_worldTransformIsCurrent = true;
    }
}

}
