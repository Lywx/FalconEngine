#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>
#include <FalconEngine/Graphics/Renderer/Scene/Light.h>

namespace FalconEngine
{

class PointLightEntity;
using PointLightEntitySharedPtr = std::shared_ptr<PointLightEntity>;

#pragma warning(disable: 4251)
class FALCON_ENGINE_ITEM_GRAPHICS PointLightEntity : public Entity
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PointLightEntity(const NodeSharedPtr node);
    PointLightEntity(const NodeSharedPtr node, const LightSharedPtr light);
    ~PointLightEntity();

public:
    Color
    GetAmbient() const;

    void
    SetAmbient(Color color);

    Color
    GetDiffuse() const;

    void
    SetDiffuse(Color color);

    Color
    GetSpecular() const;

    void
    SetSpecular(Color color);

    float
    GetConstant() const;

    void
    SetConstant(float value);

    float
    GetLinear() const;

    void
    SetLinear(float value);

    float
    GetQuadratic() const;

    void
    SetQuadratic(float value);

    const Light *
    GetLight() const;

protected:
    virtual void
    UpdateLocalTransformFeedback(bool initiator) override;

protected:
    LightSharedPtr mLight;
};
#pragma warning(default: 4251)

}
