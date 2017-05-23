#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>
#include <FalconEngine/Graphics/Renderer/Scene/Light.h>
#include <FalconEngine/Graphics/Scene/SceneEntity.h>

namespace FalconEngine
{

class PointLightEntity;
using PointLightEntitySharedPtr = std::shared_ptr<PointLightEntity>;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API PointLightEntity : public SceneEntity
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PointLightEntity(const std::shared_ptr<Node> node);
    PointLightEntity(const std::shared_ptr<Node> node, const LightSharedPtr light);
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
