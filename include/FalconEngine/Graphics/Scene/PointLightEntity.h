#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>
#include <FalconEngine/Graphics/Renderer/Scene/Light.h>

namespace FalconEngine
{

class PointLightEntity;
using PointLightEntitySharedPtr = std::shared_ptr<PointLightEntity>;

class PointLightEntity : public Entity
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PointLightEntity(const NodeSharedPtr node);
    PointLightEntity(const NodeSharedPtr node, const LightSharedPtr light);

public:
    Color
    GetAmbient() const;

    void
    SetAmbient(Color);

    Color
    GetDiffuse() const;

    void
    SetDiffuse(Color);

    Color
    GetSpecular() const;

    void
    SetSpecular(Color);

    float
    GetConstant() const;

    void
    SetConstant(float);

    float
    GetLinear() const;

    void
    SetLinear(float);

    float
    GetQuadratic() const;

    void
    SetQuadratic(float);

    Vector3f
    GetPosition() const;

    void
    SetPosition(Vector3f) const;

    const Light *
    GetLight() const;

    virtual void
    Update(GameEngineInput *input, double elapsed) override;

protected:
    LightSharedPtr mLight;
};

}
