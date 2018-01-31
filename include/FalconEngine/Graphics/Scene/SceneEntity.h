#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>

namespace FalconEngine
{

class SceneEntity;

class FALCON_ENGINE_API SceneEntity : public Entity
{
public:
    SceneEntity();
    explicit SceneEntity(const std::shared_ptr<Node>& node);
    virtual ~SceneEntity() = default;

public:
    virtual void
    Update(GameEngineInput *input, double elapsed) override;
};

}