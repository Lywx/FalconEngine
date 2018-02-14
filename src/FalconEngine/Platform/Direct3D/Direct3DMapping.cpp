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

    if (texture->GetAttachmentEnabled(TextureMode::Color))
    {
        bindFlag += D3D11_BIND_RENDER_TARGET;
    }

    if (texture->GetAttachmentEnabled(TextureMode::DepthStencil))
    {
        bindFlag += D3D11_BIND_DEPTH_STENCIL;
    }

    if (texture->GetAttachmentEnabled(TextureMode::Image))
    {
        bindFlag += D3D11_BIND_UNORDERED_ACCESS;
    }

    if (texture->GetAttachmentEnabled(TextureMode::Texture))
    {
        bindFlag += D3D11_BIND_SHADER_RESOURCE;
    }

    return bindFlag;
}

const DXGI_FORMAT Direct3DResourceFormat[int(TextureFormat::Count)] =
{
    DXGI_FORMAT_UNKNOWN,           // None

    DXGI_FORMAT_D16_UNORM,         // D16_UNORM
    DXGI_FORMAT_D24_UNORM_S8_UINT, // D24_UNORM_S8_UINT
    DXGI_FORMAT_R8G8B8A8_UINT,     // R8G8B8A8_UINT
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

const D3D11_BLEND Direct3DBlendFactor[int(BlendFactor::Count)] =
{
    D3D11_BLEND_ZERO,             // ZERO
    D3D11_BLEND_ONE,              // ONE
    D3D11_BLEND_SRC_COLOR,        // SRC_COLOR
    D3D11_BLEND_INV_SRC_COLOR,    // ONE_MINUS_SRC_COLOR
    D3D11_BLEND_DEST_COLOR,       // DST_COLOR
    D3D11_BLEND_INV_DEST_COLOR,   // ONE_MINUS_DST_COLOR
    D3D11_BLEND_SRC_ALPHA,        // SRC_ALPHA
    D3D11_BLEND_INV_SRC_ALPHA,    // ONE_MINUS_SRC_ALPHA
    D3D11_BLEND_DEST_ALPHA,       // DST_ALPHA
    D3D11_BLEND_INV_DEST_ALPHA,   // ONE_MINUS_DST_ALPHA
    D3D11_BLEND_BLEND_FACTOR,     // CONSTANT_COLOR
    D3D11_BLEND_INV_BLEND_FACTOR, // ONE_MINUS_CONSTANT_COLOR

    // NOTE(Wuxiang): Not supported in Direct3D.
    // D3D11_BLEND(0),               // CONSTANT_ALPHA
    // D3D11_BLEND(0),               // ONE_MINUS_CONSTANT_ALPHA

    D3D11_BLEND_SRC_ALPHA_SAT,    // SRC_ALPHA_SATURATE
    D3D11_BLEND_SRC1_COLOR,       // SRC1_COLOR
    D3D11_BLEND_INV_SRC1_COLOR,   // ONE_MINUS_SRC1_COLOR
    D3D11_BLEND_SRC1_ALPHA,       // SRC1_ALPHA
    D3D11_BLEND_INV_SRC1_ALPHA,   // ONE_MINUS_SRC1_ALPHA
};

const D3D11_BLEND_OP Direct3DBlendOperator[int(BlendOperator::Count)] =
{
    D3D11_BLEND_OP_ADD,          // Add
    D3D11_BLEND_OP_SUBTRACT,     // Subtract
    D3D11_BLEND_OP_REV_SUBTRACT, // ReverseSubtract
    D3D11_BLEND_OP_MIN,          // Min
    D3D11_BLEND_OP_MAX           // Max
};

const D3D11_LOGIC_OP Direct3DLogicOperator[int(LogicOperator::Count)] =
{
    D3D11_LOGIC_OP_CLEAR,         // Clear
    D3D11_LOGIC_OP_SET,           // Set
    D3D11_LOGIC_OP_COPY,          // Copy
    D3D11_LOGIC_OP_COPY_INVERTED, // CopyInverted
    D3D11_LOGIC_OP_NOOP,          // Noop
    D3D11_LOGIC_OP_INVERT,        // Invert
    D3D11_LOGIC_OP_AND,           // And
    D3D11_LOGIC_OP_NAND,          // Nand
    D3D11_LOGIC_OP_OR,            // Or
    D3D11_LOGIC_OP_NOR,           // Nor
    D3D11_LOGIC_OP_XOR,           // Xor
    D3D11_LOGIC_OP_EQUIV,         // Equiv
    D3D11_LOGIC_OP_AND_REVERSE,   // AndReverse
    D3D11_LOGIC_OP_AND_INVERTED,  // AndInverted
    D3D11_LOGIC_OP_OR_REVERSE,    // OrReverse
    D3D11_LOGIC_OP_OR_INVERTED,   // OrInverted
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