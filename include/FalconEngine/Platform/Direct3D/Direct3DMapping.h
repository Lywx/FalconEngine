#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Primitive.h>
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>

namespace FalconEngine
{

FALCON_ENGINE_API extern const D3D11_MAP                  Direct3DBufferAccessMode[int(ResourceMapAccessMode::Count)];
FALCON_ENGINE_API extern const int                        Direct3DBufferFlushModeMark[int(ResourceMapFlushMode::Count)];
FALCON_ENGINE_API extern const int                        Direct3DBufferSynchronizationModeMark[int(ResourceMapSyncMode::Count)];

FALCON_ENGINE_API extern const D3D11_USAGE                Direct3DResourceUsage[int(FALCON_ENGINE_RESOURCE_ACCESS_COUNT)];

FALCON_ENGINE_API extern const DXGI_FORMAT                Direct3DTextureFormat[int(TextureFormat::Count)];

FALCON_ENGINE_API extern const D3D11_TEXTURE_ADDRESS_MODE Direct3DSamplerWrapMode[int(SamplerWrapMode::Count)];

FALCON_ENGINE_API extern const int                        Direct3DBlendFactorSource[int(BlendSourceFactor::Count)];
FALCON_ENGINE_API extern const int                        Direct3DBlendFactorDestination[int(BlendDestinationFactor::Count)];

FALCON_ENGINE_API extern const int                        Direct3DDepthFunction[int(DepthFunction::Count)];

FALCON_ENGINE_API extern const int                        Direct3DStencilFunction[int(StencilFunction::Count)];
FALCON_ENGINE_API extern const int                        Direct3DStencilOperation[int(StencilOperation::Count)];

FALCON_ENGINE_API extern const DXGI_FORMAT                Direct3DShaderAttributeFormat[int(VertexAttributeType::Count)];
FALCON_ENGINE_API extern const int                        Direct3DShaderType[int(ShaderType::Count)];

FALCON_ENGINE_API extern const D3D11_PRIMITIVE_TOPOLOGY   Direct3DPrimitiveType[int(PrimitiveType::Count)];

}

#endif