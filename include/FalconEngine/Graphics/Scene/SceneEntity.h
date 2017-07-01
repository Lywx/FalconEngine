#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>

namespace FalconEngine
{

class SceneEntity;

class FALCON_ENGINE_API SceneEntity : public Entity
{
public:
    SceneEntity();
    explicit SceneEntity(std::shared_ptr<Node> node);
    virtual ~SceneEntity() = default;

public:
    virtual void
    Update(GameEngineInput *input, double elapsed) override;
};

}