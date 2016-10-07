#pragma once

#include <FalconEngine/CoreInclude.h>

// Begin Microsoft Windows DLL support.
#if defined(FALCON_ENGINE_GRAPHICS_DLL_EXPORT)
// For the DLL library.
#define FALCON_ENGINE_GRAPHICS_ITEM __declspec(dllexport)
#elif defined(FALCON_ENGINE_GRAPHICS_DLL_IMPORT)
// For a client of the DLL library.
#define FALCON_ENGINE_GRAPHICS_ITEM __declspec(dllimport)
#else
// For the static library and for Apple/Linux.
#define FALCON_ENGINE_GRAPHICS_ITEM
#endif
// End Microsoft Windows DLL support.

// Enable this define to verify that the camera axis directions form a
// right-handed orthonormal set.  The test is done only once, because
// numerical round-off errors during rotations of the frame over time
// may require a renormalization of the frame.
#ifdef _DEBUG
#define FALCON_ENGINE_VALIDATE_CAMERA_FRAME_ONCE
#endif

// Expose this define to allow resetting of render state and other state in
// the Renderer::Draw (const Visual*, const VisualEffectInstance*) call.
//#define FALCON_ENGINE_RESET_STATE_AFTER_DRAW

// Enable this to allow counting the number of pixels drawn in
// Renderer::DrawPrimitive.
//#define FALCON_ENGINE_QUERY_PIXEL_COUNT

// Enable this to draw text using display lists in OpenGL; otherwise, text is
// drawn manually using bitmapped fonts.
#ifdef FALCON_ENGINE_USE_OPENGL

// Some OpenGL 2.x drivers are not handling normal attributes correctly.
// This is a problem should you want to use the normal vector to pass a
// 4-tuple of information to the shader.  The OpenGL 1.x glNormalPointer
// assumes the normals are 3-tuples.  If you know that your target
// machines correctly support OpenGL 2.x normal attributes, expose the
// following #define.  Otherwise, the renderer will use the OpenGL 1.x
// glNormalPointer.
//
// On the Macintosh, whether PowerPC or Intel, with NVIDIA graphics cards,
// the generic attributes for normals does not work.  This happens because
// we are using OpenGL 1.x extensions for shader programming.  We need to
// update to OpenGL 2.x and later.
#ifndef __APPLE__
#define FALCON_ENGINE_USE_OPENGL2_NORMAL_ATTRIBUTES
#endif
#endif

// Enables checking of various data in the DX9 renderer.
#ifdef FALCON_ENGINE_USE_DX9
#ifdef _DEBUG
#define FALCON_ENGINE_PDR_DEBUG
#endif
#endif
