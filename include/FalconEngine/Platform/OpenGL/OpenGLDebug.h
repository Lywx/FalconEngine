#pragma once

#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

#if defined(FALCON_ENGINE_API_OPENGL)
namespace FalconEngine
{

void
CheckOpenGLError();

const char *
GetOpenGLDebugSourceString(GLenum source);

const char *
GetOpenGLDebugTypeString(GLenum type);

const char *
GetOpenGLDebugSeverityString(GLenum severity);

unsigned int
GetOpenGLDebugColorString(GLenum severity);

void
OpenGLDebugCallback(
    GLenum        source,
    GLenum        type,
    GLuint        id,
    GLenum        severity,
    GLsizei    /* length */,
    const GLchar *message,
    GLvoid   * /* userParam */);

void
OpenGLDebugInitialize();

}

#endif