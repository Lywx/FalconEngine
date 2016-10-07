#pragma once

#include <memory>

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Graphics/Bound.h>
#include <FalconEngine/Graphics/Controllers/ControlledObject.h>
#include <FalconEngine/Graphics/Transform.h>

namespace FalconEngine {

// @Remark: Improvement based on David Eberly's Wild Magic:
//     1. Added dirty flag pattern for WorldTransform data.
class FALCON_ENGINE_GRAPHICS_ITEM Spatial : public ControlledObject
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

    // @Summary: Local transform from parent
    Transform LocalTransform;

    // @Summary: World transform from model space to world space if this instance has
    // no parent.
    //
    // In some situations you might need to set the world transform directly
    // and bypass the Spatial::Update() mechanism.  If World is set directly,
    // the mWorldIsCurrent flag should be set to 'true'.
    Transform WorldTransform;
    bool      WorldTransformIsCurrent = false;

    // @Summary: World bound access.  In some situations you might want to set the
    // world bound directly and bypass the Spatial::Update() mechanism.  If
    // mWorldBound is set directly, the mWorldBoundIsCurrent flag should be
    // set to 'true'.
    Bound WorldBound;
    bool  WorldBoundIsCurrent;

    // @Remark: Because the child would not need to manage the lifetime of its
    // parent, it allows child to use get / set on parent conveniently without
    // caring memory management. Using raw pointer here won't affect the code
    // that needs to check parent exists.
    Spatial *Parent;

protected:
    virtual void UpdateWorldTransform(double elapsed);
    virtual void UpdateWorldBound() = 0;
    void         UpdateWorldBoundPropagation();
};

typedef std::shared_ptr<Spatial> SpatialPtr;

#include "Spatial.inl"

}
