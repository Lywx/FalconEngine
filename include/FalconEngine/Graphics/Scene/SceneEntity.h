#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>

namespace FalconEngine
{

class SceneEntity;
using SceneEntitySharedPtr = std::shared_ptr<SceneEntity>;

class FALCON_ENGINE_API SceneEntity : public Entity
{
public:
    SceneEntity();
    explicit SceneEntity(NodeSharedPtr node);
    virtual ~SceneEntity() = default;

public:
    virtual void
    Update(GameEngineInput *input, double elapsed) override;
};

}