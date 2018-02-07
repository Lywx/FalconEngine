#pragma once

#include <FalconEngine/Core/Macro.h>

namespace FalconEngine
{

enum class ResourceCreationAccessMode
{
    None,

    // NOTE(Wuxiang): D3D11_USAGE_STAGING is not be able to map to OpenGL usage hint.
    // So I am taking the greatest common divisor here.
    //
    //                        // Direct3D                OpenGL
    GpuRead,                  // D3D11_USAGE_IMMUTABLE   GL_STATIC_DRAW
    GpuReadCpuWrite,          // D3D11_USA6E_DYNAMIC     GL_STATIC_DRAW, GL_STREAM_DRAW, GL_DYNAMIC_DRAW
    GpuReadWrite,             // D3D11_USAGE_DEFAULT     GL_STATIC_COPY, GL_STREAM_COPY, GL_DYNAMIC_COPY
//  GpuReadWriteCpuReadWrite, // D3D11_USAGE_STAGING     GL_STATIC_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_DYNAMIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, GL_STREAM_COPY, GL_STREAM_DRAW, GL_STREAM_READ
    GpuWriteCpuRead,          // D3D11_USAGE_STAGING     GL_STATIC_READ, GL_STREAM_READ, GL_DYNAMIC_READ

    Count,
};

enum class ResourceCreationAccessUsage
{
    None,    // Direct3D   OpenGL

    Static,  // *          GL_STATIC_XXX. OpenGL may decide to
//  shuffle the data around internally in order to make it fit in memory better,
//  or be a more optimal data format. This may be an expensive operation, but
//  since the data is static, it needs to be performed only once and so the
//  payoff may be great.

    Stream,  // *          GL_STREAM_XXX. This indicates that you’re planning
//  on regularly modifying the data in the buffer and using it only a few times
//  (maybe only once) between each modification.

    Dynamic, // *          GL_DYNAMIC_XXX. Indicates that you’re going to change
//  the data from time to time but will probably use it many times between
//  modifications.

    Count
};

// NOTE(Wuxiang): Resource in OpenGL and Direct3D has different model. Because
// OpenGL only has texture view to manipulate how the resource is read, while
// Direct3D 11 widely accepts different view of the same resource. I decide that
// because the engine design would consider the greatest common divisor of both
// API. So you won't be able to use some of Direct3D feature to attach resource
// for multiple view.
//
// Resource                OpenGL                         Direct3D
//
// Vertex Buffer           GL_ARRAY_BUFFER                D3D11_BIND_VERTEX_BUFFER
// Index Buffer            GL_ELEMENT_ARRAY_BUFFER        D3D11_BIND_INDEX_BUFFER
// Shader Buffer           GL_SHADER_STORAGE_BUFFER       D3D11_BIND_UNORDERED_ACCESS
// Uniform Buffer          GL_UNIFORM_BUFFER              D3D11_BIND_CONSTANT_BUFFER
// Texture                 GL_PIXEL_UNPACK_BUFFER         D3D11_BIND_SHADER_RESOURCE
// Texture Buffer          GL_TEXTURE_BUFFER              D3D11_BIND_SHADER_RESOURCE
// Image                   GL_PIXEL_UNPACK_BUFFER         D3D11_BIND_UNORDERED_ACCESS
// Render Buffer           GL_RENDERBUFFER                D3D11_BIND_RENDER_TARGET
// Depth Stencil Buffer    GL_PIXEL_UNPACK_BUFFER         D3D11_BIND_DEPTH_STENCIL
// Feedback Buffer         GL_TRANSFORM_FEEDBACK_BUFFER   D3D11_BIND_STREAM_OUTPUT

enum class ResourceMapAccessMode
{
    WriteBuffer,
    WriteBufferInvalidateBuffer, // Enable buffer orphaning to avoid implicit synchronization.
    WriteRange,
    WriteRangeInvalidateBuffer,  // Enable buffer orphaning to avoid implicit synchronization.
    WriteRangeInvalidateRange,

    ReadWriteBuffer,
    ReadWriteRange,

    ReadBuffer,
    ReadRange,

    Count
};

enum class ResourceMapFlushMode
{
    Automatic,
    Explicit,

    Count,
};

enum class ResourceMapSyncMode
{
    Synchronized,
    Unsynchronized,

    Count,
};

// @summary Indicate buffer storage resides on 1) RAM and VRAM or 2) VRAM only.
enum class ResourceStorageMode
{
    None,

    Device, // Buffer resides on VRAM only, accessible by CPU only in pinned memory.
    Host,   // Buffer resides on RAM, explicitly copied to VRAM.

    Count
};

}
