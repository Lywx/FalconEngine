#pragma once

#include <FalconEngine/Core/Macro.h>

namespace FalconEngine
{

enum class ResourceCreationAccessMode
{
    None,

    // NOTE(Wuxiang): D3D11_USAGE_STAGING is not be able to map to OpenGL usage hint.
    // So I am taking the most common denominator here.
    //
    //                         // Direct3D              / OpenGL
    GpuRead,                   // D3D11_USAGE_IMMUTABLE   GL_STATIC_DRAW
    GpuRead_CpuWrite,          // D3D11_USA6E_DYNAMIC     GL_STATIC_DRAW, GL_STREAM_DRAW, GL_DYNAMIC_DRAW
    GpuReadWrite,              // D3D11_USAGE_DEFAULT     GL_STATIC_COPY, GL_STREAM_COPY, GL_DYNAMIC_COPY
//  GpuReadWrite_CpuReadWrite, // D3D11_USAGE_STAGING     GL_STATIC_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_DYNAMIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, GL_STREAM_COPY, GL_STREAM_DRAW, GL_STREAM_READ
    GpuWrite_CpuRead,          // D3D11_USAGE_STAGING     GL_STATIC_READ, GL_STREAM_READ, GL_DYNAMIC_READ

    Count,
};

enum class ResourceCreationAccessUsage
{
    None,    // Direct3D / OpenGL

    Static,  //            GL_STATIC_XXX
    Stream,  //            GL_STREAM_XXX
    Dynamic, //            GL_DYNAMIC_XXX

    Count
};

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

}
