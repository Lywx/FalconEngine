#pragma once

#include <FalconEngine/Math/Common.h>

#include <FalconEngine/Math/Matrix4.h>
#include <FalconEngine/Math/Vector3.h>

#include <FalconEngine/Math/Bound/BoundingBox.h>

namespace FalconEngine
{

#pragma warning(disable : 4251)
class FALCON_ENGINE_API AABB final : public BoundingBox
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static std::vector<Vector3f>
    GetUnitPositionList();

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit AABB(Vector3f position);
    virtual ~AABB() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @summary Get the transform matrix that could transform normalized bounding
    // box position (unit cube) into model space position of bounding box.
    Matrix4f
    GetModelPositionTransform() const;

    virtual int
    GetModelPositionNum() const override;

    virtual std::vector<Vector3f>
    GetModelPositionList() const override;

    void
    UpdatePosition(Vector3f position);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    InitializePosition(Vector3f position);

public:
    float mXmax;
    float mXmin;

    float mYmax;
    float mYmin;

    float mZmax;
    float mZmin;

private:
    bool                          mInitialized;
    mutable std::vector<Vector3f> mModelPosition;
    mutable bool                  mModelPositionInitialized;
};
#pragma warning(default : 4251)

}
