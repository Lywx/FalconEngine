#pragma once

#include <FalconEngine/Core/Common.h>

#include <functional>

#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Math/Matrix4.h>

namespace FalconEngine
{

class Spatial;
using SpatialSharedPtr = std::shared_ptr<Spatial>;

class FALCON_ENGINE_API Spatial : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

protected:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Spatial();

public:
    virtual ~Spatial();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    const Spatial *
    GetParent() const;

    void
    SetParent(Spatial *parent);

    // @summary Update everything that need to constantly update themselves.
    // @param initiator - if the caller is the initiator of this round of update. If
    //     so, we need to update the bounding volume in parent because the
    //     bounding volume is computed from leaves to root.
    virtual void
    Update(double elapsed, bool initiator);

    /************************************************************************/
    /* Deep and Shallow Copy                                                */
    /************************************************************************/
    // @remark This method use return type covariance in the class hierarchy.
    // @return The clone of this Spatial instance. Grant for no shared ownership.
    virtual Spatial *
    GetClone() const = 0;

    void
    CopyTo(Spatial *lhs) const;

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    virtual void UpdateWorldTransform(double elapsed);

public:
    // @summary Local transform from parent
    Matrix4f mLocalTransform;

    // @summary World transform from model space to world space if this instance has
    // no parent.
    //
    // In some situations you might need to set the world transform directly
    // and bypass the Spatial::Update() mechanism.  If World is set directly,
    // the WorldIsCurrent flag should be set to 'true'.
    Matrix4f mWorldTransform;
    bool     mWorldTransformIsCurrent = false;

    // @note Because the child would not need to manage the lifetime of its
    // parent, it allows child to use get / set on parent conveniently without
    // caring memory management. Using raw pointer here won't affect the code
    // that needs to check parent exists.
    Spatial *mParent;
};

}
