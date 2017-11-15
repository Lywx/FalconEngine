#pragma once

#include <FalconEngine/Core/Common.h>

#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>
#include <FalconEngine/Graphics/Scene/SceneEntity.h>

namespace FalconEngine
{

class FALCON_ENGINE_API CharacterEntity : public SceneEntity
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    explicit CharacterEntity(const std::shared_ptr<Node>& node);
    virtual ~CharacterEntity();
};

}
