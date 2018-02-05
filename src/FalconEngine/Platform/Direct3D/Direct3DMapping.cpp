#include <FalconEngine/Platform/Direct3D/Direct3DMapping.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)

namespace FalconEngine
{

const D3D11_MAP Direct3DBufferAccessMode[int(ResourceMapAccessMode::Count)] =
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

    // TODO(Wuxiang): Add non overwrite support.
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476181(v=vs.85).aspx
    D3D11_MAP_WRITE_NO_OVERWRITE
};

const D3D11_USAGE Direct3DResourceUsage[int(FALCON_ENGINE_RESOURCE_ACCESS_COUNT)] =
{
    D3D11_USAGE(-1),       // FALCON_ENGINE_RESOURCE_ACCESS_NONE

    D3D11_USAGE_IMMUTABLE, // ResourceCreationAccessMode::GpuRead
    D3D11_USAGE_DYNAMIC,   // ResourceCreationAccessMode::GpuRead_CpuWrite
    D3D11_USAGE_DEFAULT,   // ResourceCreationAccessMode::GpuReadWrite
    D3D11_USAGE_STAGING    // ResourceCreationAccessMode::GpuWrite_CpuRead
};

const DXGI_FORMAT Direct3DTextureFormat[int(TextureFormat::Count)] =
{
    DXGI_FORMAT_UNKNOWN,       // None

    DXGI_FORMAT_R8G8B8A8_UINT, // R8G8B8A8
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