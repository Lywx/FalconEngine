#include <FalconEngine/Platform/Direct3D/Direct3DMapping.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Core/Exception.h>

namespace FalconEngine
{

const D3D11_USAGE Direct3DResourceAccessUsage[int(ResourceCreationAccessMode::Count)] =
{
    D3D11_USAGE(-1),       // None

    D3D11_USAGE_IMMUTABLE, // GpuRead
    D3D11_USAGE_DYNAMIC,   // GpuReadCpuWrite
    D3D11_USAGE_DEFAULT,   // GpuReadWrite
    D3D11_USAGE_STAGING    // GpuWriteCpuRead
};

UINT
Direct3DResourceAccessFlag(ResourceCreationAccessMode mode)
{
    if (mode == ResourceCreationAccessMode::GpuReadCpuWrite)
    {
        return D3D11_CPU_ACCESS_WRITE;
    }
    else if (mode == ResourceCreationAccessMode::GpuWriteCpuRead)
    {
        return D3D11_CPU_ACCESS_READ;
    }
    else
    {
        return 0;
    }
}

UINT
Direct3DResourceBindFlag(const Buffer *buffer)
{
    UINT bindFlag = 0;

    switch (buffer->GetBufferType())
    {
    case BufferType::VertexBuffer:
        bindFlag = D3D11_BIND_VERTEX_BUFFER;
        break;
    case BufferType::IndexBuffer:
        bindFlag = D3D11_BIND_INDEX_BUFFER;
        break;
    case BufferType::ShaderBuffer:
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        break;
    case BufferType::UniformBuffer:
        bindFlag = D3D11_BIND_CONSTANT_BUFFER;
        break;
    case BufferType::TextureBuffer:
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        break;
    case BufferType::FeedbackBuffer:
        bindFlag = D3D11_BIND_STREAM_OUTPUT;
        break;
    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION()
    }

    return bindFlag;
}

UINT
Direct3DResourceBindFlag(const Texture *texture)
{
    UINT bindFlag = 0;

    if (texture->mAttachColorBuffer)
    {
        bindFlag += D3D11_BIND_RENDER_TARGET;
    }

    if (texture->mAttachDepthStencilBuffer)
    {
        bindFlag += D3D11_BIND_DEPTH_STENCIL;
    }

    if (texture->mAttachImage)
    {
        bindFlag += D3D11_BIND_UNORDERED_ACCESS;
    }

    if (texture->mAttachTexture)
    {
        bindFlag = D3D11_BIND_SHADER_RESOURCE;
    }

    return bindFlag;
}

const DXGI_FORMAT Direct3DResourceFormat[int(TextureFormat::Count)] =
{
    DXGI_FORMAT_UNKNOWN,       // None

    DXGI_FORMAT_R8G8B8A8_UINT, // R8G8B8A8
};

const D3D11_MAP Direct3DResourceMapMode[int(ResourceMapAccessMode::Count)] =
{
    D3D11_MAP_WRITE,
    D3D11_MAP_WRITE_DISCARD,
    D3D11_MAP_WRITE,
    D3D11_MAP_WRITE_DISCARD,
    D3D11_MAP_WRITE_DISCARD,

    D3D11_MAP_READ_WRITE,
    D3D11_MAP_READ_WRITE,

    D3D11_MAP_READ,
    D3D11_MAP_READ,

    // TODO(Wuxiang): 2018-02-06 12:10 Add non overwrite support.
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476181(v=vs.85).aspx
    D3D11_MAP_WRITE_NO_OVERWRITE
};

const D3D11_TEXTURE_ADDRESS_MODE Direct3DSamplerWrapMode[int(SamplerWrapMode::Count)] =
{
    D3D11_TEXTURE_ADDRESS_BORDER, // ClampToBorder
    D3D11_TEXTURE_ADDRESS_CLAMP,  // ClampToEdge
    D3D11_TEXTURE_ADDRESS_WRAP,   // Repeat
    D3D11_TEXTURE_ADDRESS_MIRROR, // RepeatMirrored

    // TODO(Wuxiang): Add one more option to SamplerWrapMode to support D3D11_TEXTURE_ADDRESS_MIRROR_ONCE.
};

// https://msdn.microsoft.com/en-us/library/windows/desktop/bb173059(v=vs.85).aspx
const DXGI_FORMAT Direct3DShaderAttributeFormat[int(VertexAttributeType::Count)] =
{
    DXGI_FORMAT_UNKNOWN,            // None

    DXGI_FORMAT_R32_FLOAT,          // Float
    DXGI_FORMAT_R32G32_FLOAT,       // FloatVec2
    DXGI_FORMAT_R32G32B32_FLOAT,    // FloatVec3
    DXGI_FORMAT_R32G32B32A32_FLOAT, // FloatVec4

    DXGI_FORMAT_R32_SINT,           // Int
    DXGI_FORMAT_R32G32_SINT,        // IntVec2
    DXGI_FORMAT_R32G32B32_SINT,     // IntVec3
    DXGI_FORMAT_R32G32B32A32_SINT   // IntVec4
};

const D3D11_PRIMITIVE_TOPOLOGY Direct3DPrimitiveType[int(PrimitiveType::Count)] =
{
    D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED,     // None
    D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,     // Point
    D3D11_PRIMITIVE_TOPOLOGY_LINELIST,      // Line
    D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,     // LineStrip
    D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,  // Triangle
    D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, // TriangleStrip
};

}

#endif