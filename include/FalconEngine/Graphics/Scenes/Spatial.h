#pragma once

#include <memory>

#include <FalconEngine/Graphics/Controllers/ControlledObject.h>
#include <FalconEngine/Graphics/Transform.h>

namespace FalconEngine {

class Spatial : public ControlledObject
{
    FALCON_ENGINE_DECLARE_RTTI;

protected:
    Spatial();

public:
    virtual ~Spatial();

    virtual void Update(double elapsed);

    // Local transform from parent
    Transform LocalTransform;

    // World transform from model space to world space if this instance has
    // no parent.
    //
    // In some situations you might need to set the world transform directly
    // and bypass the Spatial::Update() mechanism.  If World is set directly,
    // the mWorldIsCurrent flag should be set to 'true'.
    Transform WorldTransform;
    bool      WorldTransformIsCurrent = false;

    // World bound access.  In some situations you might want to set the
    // world bound directly and bypass the Spatial::Update() mechanism.  If
    // mWorldBound is set directly, the mWorldBoundIsCurrent flag should be
    // set to 'true'.
    Bound WorldBound;
    bool  WorldBoundIsCurrent;

    Spatial *Parent = nullptr;

protected:
    virtual void UpdateWorldData(double elapsed);
    virtual void UpdateWorldBound() = 0;
    void         UpdateWorldBoundPropagation();
};

typedef std::shared_ptr<Spatial> SpatialPtr;

#include "Spatial.inl"

}
