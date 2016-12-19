#pragma once

#include <memory>

#include <FalconEngine/Core/Object.h>
#include <FalconEngine/GraphicsInclude.h>

namespace FalconEngine
{

class Spatial : public Object
{
    FALCON_ENGINE_DECLARE_RTTI;

protected:
    Spatial();

public:
    virtual ~Spatial();

    // @Summary: Update everything that need to constantly update themselves.
    // @Params:
    // initiator - if the caller is the initiator of this round of update. If
    //     so, we need to update the bounding volume in parent because the
    //     bounding volume is computed from leaves to root.
    virtual void Update(double elapsed, bool initiator);

protected:
    virtual void UpdateWorldTransform(double elapsed);

public:
    // @Summary: Local transform from parent
    Matrix4f m_localTransform;

    // @Summary: World transform from model space to world space if this instance has
    // no parent.
    //
    // In some situations you might need to set the world transform directly
    // and bypass the Spatial::Update() mechanism.  If World is set directly,
    // the WorldIsCurrent flag should be set to 'true'.
    Matrix4f m_worldTransform;
    bool     m_worldTransformIsCurrent = false;

    // @Remark: Because the child would not need to manage the lifetime of its
    // parent, it allows child to use get / set on parent conveniently without
    // caring memory management. Using raw pointer here won't affect the code
    // that needs to check parent exists.
    Spatial *m_parent;
};

typedef std::shared_ptr<Spatial> SpatialPtr;

}
