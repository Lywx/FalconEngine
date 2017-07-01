#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>
#include <FalconEngine/Graphics/Renderer/Scene/Light.h>
#include <FalconEngine/Graphics/Scene/SceneEntity.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API LightEntity : public SceneEntity
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit LightEntity(const std::shared_ptr<Node> node, LightType lightType);
    LightEntity(const std::shared_ptr<Node> node, const std::shared_ptr<Light> light);
    ~LightEntity();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
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

    Vector3f
    GetDirection() const;

    void
    SetDirection(Vector3f direciton);

    const Light *
    GetLight() const;

    std::shared_ptr<Light>
    GetLight();

protected:
    virtual void
    UpdateLocalTransformFeedback(bool initiator) override;

protected:
    std::shared_ptr<Light> mLight;
};
#pragma warning(default: 4251)

}
