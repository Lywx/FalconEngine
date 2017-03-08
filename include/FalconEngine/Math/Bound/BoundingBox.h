#pragma once

#include <FalconEngine/MathInclude.h>

#include <vector>

#include <FalconEngine/Math/Matrix4.h>
#include <FalconEngine/Math/Vector3.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

class BoundingBoxVertexTransform
{
public:
    Matrix4f mModelViewPrjectionTransform;
};

#pragma pack(push, 1)
class BoundingBoxVertex
{
public:
    Vector3f mPosition;
    Vector4f mColor;
};
#pragma pack(pop)

class BoundingBox
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    BoundingBox();
    virtual ~BoundingBox();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    virtual int
    GetPositionNum() const = 0;

    virtual std::vector<Vector3f>
    GetPositionList() const = 0;
};

}
