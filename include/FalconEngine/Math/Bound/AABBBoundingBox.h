#pragma once

#include <FalconEngine/Math/Header.h>
#include <FalconEngine/Math/Matrix4.h>
#include <FalconEngine/Math/Vector3.h>
#include <FalconEngine/Math/Bound/BoundingBox.h>

namespace FalconEngine
{

#pragma warning(disable : 4251)
class FALCON_ENGINE_ITEM_MATH AABBBoundingBox final : public BoundingBox
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static std::vector<Vector3f>
    GetCubeModelPositionList();

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit AABBBoundingBox(Vector3f position);
    virtual ~AABBBoundingBox() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    Matrix4f
    GetCubeModelPositionTransform() const;

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
