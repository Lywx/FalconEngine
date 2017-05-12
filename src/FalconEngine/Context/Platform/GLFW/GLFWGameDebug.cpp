#include <FalconEngine/Context/GameDebug.h>

#include <algorithm>

#if FALCON_ENGINE_PLATFORM_GLFW
#include <FalconEngine/Context/Platform/GLFW/GLFWHeader.h>

using namespace std;

namespace FalconEngine
{

void
glDebugCheckError()
{
    assert(glGetError() == GL_NO_ERROR);
}

const char *
GetOpenGLDebugSourceString(GLenum source)
{
    static const char *sourceNames[] =
    {
        "API",
        "Window System",
        "Shader Compiler",
        "Third Party",
        "Application",
        "Other",
        "Unknown"
    };

    auto sourceIndex = min<size_t>(source - GL_DEBUG_SOURCE_API, ArraySize(sourceNames) - 1);
    return sourceNames[sourceIndex];
}

const char *
GetOpenGLDebugTypeString(GLenum type)
{
    static const char *typeNames[] =
    {
        "Error",
        "Deprecated Behavior",
        "Undefined Behavior",
        "Portability",
        "Performance",
        "Other",
        "Unknown"
    };

    auto typeIndex = min<size_t>(type - GL_DEBUG_TYPE_ERROR, ArraySize(typeNames) - 1);
    return typeNames[typeIndex];
}

const char *
GetOpenGLDebugSeverityString(GLenum severity)
{
    static const char *sevirityNames[] =
    {
        "High",
        "Medium",
        "Low",
        "Notification"
    };

    auto severityIndex = min<size_t>(severity - GL_DEBUG_SEVERITY_HIGH, ArraySize(sevirityNames) - 1);
    return sevirityNames[severityIndex];
}

unsigned int
glDebugColorString(GLenum severity)
{
    static unsigned int sevirityColors[] =
    {
        0xff0000ff, // High (Red)
        0xff00ffff, // Med  (Yellow)
        0xff00ff00, // Low  (Green)
        0xffffffff  // ???  (White)
    };

    auto severityIndex = min<size_t>(severity - GL_DEBUG_SEVERITY_HIGH, ArraySize(sevirityColors) - 1);
    return sevirityColors[severityIndex];
}

void
OpenGLDebugCallback(
    GLenum        source,
    GLenum        type,
    GLuint        id,
    GLenum        severity,
    GLsizei    /* length */,
    const GLchar *message,
    GLvoid   * /* userParam */)
{
    // Only break on high severity.
    if (severity == GL_DEBUG_SEVERITY_HIGH)
    {
        Debug::OutputString("OpenGL Error:\n");
        Debug::OutputString("=============\n");
        Debug::OutputString(string("Object:    ") + to_string(id) + "\n");
        Debug::OutputString(string("Severity:  ") + GetOpenGLDebugSeverityString(severity) + "\n");
        Debug::OutputString(string("Type:      ") + GetOpenGLDebugTypeString(type) + "\n");
        Debug::OutputString(string("Source:    ") + GetOpenGLDebugSourceString(source) + "\n");
        Debug::OutputString(string("Message:   ") + message + "\n");

        // Trigger a breakpoint in gDEBugger...
        glFinish();

        // Trigger a breakpoint in traditional debuggers...
        Debug::Break();
    }
}

void
OpenGLDebugInitialize()
{
    if (glDebugMessageControl != NULL)
    {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDebugMessageControl.xhtml
        glDebugMessageControl(
            GL_DONT_CARE, // source filter
            GL_DONT_CARE, // type filter
            GL_DONT_CARE, // severity filter
            0,            // count, which ignores ids array.
            NULL,         // ids, which is ignored when count = 0.
            GL_TRUE       // enable message
        );

        // https://www.opengl.org/sdk/docs/man/html/glDebugMessageCallback.xhtml
        glDebugMessageCallback(reinterpret_cast<GLDEBUGPROCARB>(OpenGLDebugCallback), NULL);
    }
}

void
GameDebug::Initialize()
{
    OpenGLDebugInitialize();
}

}

#endif
