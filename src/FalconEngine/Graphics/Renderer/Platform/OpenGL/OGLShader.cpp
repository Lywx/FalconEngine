#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLShader.h>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Context/GameDebug.h>
#include <FalconEngine/Content/Path.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderSource.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>

using namespace std;

namespace FalconEngine
{

void
ProcessShaderInclude(
    _IN_OUT_ std::string&       shaderSourceString,
    _IN_     const std::string& shaderExtensionLine,
    _IN_     const std::string& shaderPath,
    _IN_OUT_ int&               extensionBeginIndex)
{
    using namespace boost;

    static vector<string> shaderExtensionSymbols;
    shaderExtensionSymbols.clear();
    split(shaderExtensionSymbols, shaderExtensionLine, is_any_of(" "));

    if (shaderExtensionSymbols.front() != "#include")
    {
        return;
    }

    auto includeFileName = shaderExtensionSymbols.back();
    trim_if(includeFileName, is_any_of("\""));
    auto includeFilePath = GetFileDirectory(shaderPath) + includeFileName;

    auto assetManager = AssetManager::GetInstance();
    auto includeSource = assetManager->LoadShaderSource(includeFilePath);
    shaderSourceString.insert(extensionBeginIndex, includeSource->mSource);
    extensionBeginIndex += int(includeSource->mSource.size());
}

void
ProcessShaderExtension(
    _IN_OUT_ std::string&       shaderSourceString,
    _IN_OUT_ std::string&       shaderExtension,
    _IN_     const std::string& shaderPath,
    _IN_OUT_ int&               extensionBeginIndex)
{
    using namespace boost;

    static vector<string> shaderExtensionLines;
    shaderExtensionLines.clear();

    trim(shaderExtension);
    split(shaderExtensionLines, shaderExtension, is_any_of("\n"));
    for (auto& shaderExtensionLine : shaderExtensionLines)
    {
        trim(shaderExtensionLine);
        if (!shaderExtensionLine.empty())
        {
            ProcessShaderInclude(shaderSourceString, shaderExtensionLine, shaderPath, extensionBeginIndex);
        }
    }
}

// ReSharper disable once CppNotAllPathsReturnValue
string
ExtractShaderExtension(
    _IN_OUT_ std::string& shaderSourceString,
    _OUT_    int&         extensionHeaderBeginIndex)
{
    static const string extensionHeaderBeginString = "#fe_extension : enable";
    static const string extensionHeaderEndString   = "#fe_extension : disable";

    extensionHeaderBeginIndex = int(shaderSourceString.find(extensionHeaderBeginString));
    auto extensionHeaderEndIndex = int(shaderSourceString.find(extensionHeaderEndString));

    auto extensionHeaderBeginFound = extensionHeaderBeginIndex != string::npos;
    auto extensionHeaderEndFound = extensionHeaderEndIndex != string::npos;

    if (extensionHeaderBeginFound && extensionHeaderEndFound
            && extensionHeaderEndIndex > extensionHeaderBeginIndex)
    {
        auto extensionContentBeginIndex = extensionHeaderBeginIndex + extensionHeaderBeginString.size();
        auto extensionContentEndIndex = extensionHeaderEndIndex - 1;
        string extensionContent = shaderSourceString.substr(extensionContentBeginIndex,
                                  extensionContentEndIndex - extensionContentBeginIndex);

        shaderSourceString.erase(extensionHeaderBeginIndex,
                                 extensionHeaderEndIndex - extensionHeaderBeginIndex
                                 + extensionHeaderEndString.size());

        return extensionContent;
    }
    else if (!extensionHeaderBeginFound && !extensionHeaderEndFound)
    {
        return "";
    }
    else
    {
        FALCON_ENGINE_THROW_EXCEPTION("Extension is not defined correctly.");
    }
}

void
ProcessShaderSource(ShaderSource *shaderSource)
{
    auto extensionBeginIndex = 0;
    auto extensionContent = ExtractShaderExtension(shaderSource->mSource, extensionBeginIndex);
    ProcessShaderExtension(shaderSource->mSource, extensionContent, shaderSource->mFilePath, extensionBeginIndex);
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformShader::PlatformShader(Shader *shader) :
    mProgram(0),
    mShaderNum(0)
{
    // Initialize to zero.
    std::fill_n(mShaders, int(ShaderType::Count), 0);

    // Compile all shader source.
    for (auto& shaderIndexSourcePair : shader->mSourceTable)
    {
        auto shaderIndex = shaderIndexSourcePair.first;
        auto shaderType = shader->GetShaderType(shaderIndex);
        auto shaderSource = shaderIndexSourcePair.second.get();
        ProcessShaderSource(shaderSource);

        // Compile for each part of shader
        CreateFromString(shaderIndex, OpenGLShaderType[int(shaderType)], shaderSource->mSource);
    }

    // Link all the part together.
    LinkProgram();

    // Look up all the declared uniform location.
    CollectUniformLocation(shader);
}

PlatformShader::~PlatformShader()
{
    glDeleteProgram(mProgram);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformShader::CreateFromString(int shaderIndex, GLenum shaderType, const string& shaderSource)
{
    GLuint shader = glCreateShader(shaderType);

    const char *sourcePtr = shaderSource.c_str();
    glShaderSource(shader, 1, &sourcePtr, nullptr);

    // Check whether the shader loads fine
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);
        string infoLogString(infoLog);
        delete[] infoLog;

        FALCON_ENGINE_THROW_EXCEPTION("Shader compile error: " + infoLogString);
    }

    mShaders[shaderIndex] = shader;
    ++mShaderNum;
}

void
PlatformShader::LinkProgram()
{
    mProgram = glCreateProgram();

    // Avoid attach empty shaders
    if (mShaders[VertexShaderIndex] != 0)
    {
        glAttachShader(mProgram, mShaders[VertexShaderIndex]);
    }

    if (mShaders[GeometryShaderIndex] != 0)
    {
        glAttachShader(mProgram, mShaders[GeometryShaderIndex]);
    }

    if (mShaders[FragmentShaderIndex] != 0)
    {
        glAttachShader(mProgram, mShaders[FragmentShaderIndex]);
    }

    // Link and check whether the program links fine
    GLint status;
    glLinkProgram(mProgram);
    glGetProgramiv(mProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *infoLog = new GLchar[infoLogLength];
        glGetProgramInfoLog(mProgram, infoLogLength, nullptr, infoLog);
        string infoLogString(infoLog);
        delete[] infoLog;

        FALCON_ENGINE_THROW_EXCEPTION("Shader link error: " + infoLogString);
    }

    // Remove the unnecessary shader handle.
    if (mShaders[VertexShaderIndex] != 0)
    {
        glDeleteShader(mShaders[VertexShaderIndex]);
    }

    if (mShaders[GeometryShaderIndex] != 0)
    {
        glDeleteShader(mShaders[GeometryShaderIndex]);
    }

    if (mShaders[FragmentShaderIndex] != 0)
    {
        glDeleteShader(mShaders[FragmentShaderIndex]);
    }
}

void
PlatformShader::DeleteProgram() const
{
    glDeleteProgram(mProgram);
}

GLuint
PlatformShader::GetProgram() const
{
    return mProgram;
}

void
PlatformShader::Enable() const
{
    glUseProgram(mProgram);
}

void
PlatformShader::Disable() const
{
    glUseProgram(0);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformShader::CollectUniformActive()
{
    const GLsizei nameBufferSize = 64; // Maximum variable name number in GLSL
    GLchar nameArray[nameBufferSize];  // Variable name in GLSL
    GLsizei nameLength;                // Variable name length in GLSL

    GLint uniformNum;
    glGetProgramiv(mProgram, GL_ACTIVE_UNIFORMS, &uniformNum);
    GameDebug::OutputString(string("Uniforms Active: ") + std::to_string(uniformNum) + "\n");

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)
    for (auto uniformIndex = 0; uniformIndex < uniformNum; ++uniformIndex)
    {
        glGetActiveUniform(mProgram, GLuint(uniformIndex), nameBufferSize, &nameLength, &size, &type, nameArray);

        GameDebug::OutputString("Uniform #" + std::to_string(uniformIndex) + " Type:" + std::to_string(type) + " Name: " + string(nameArray) + "\n");
    }
}

void
PlatformShader::CollectUniformLocation(Shader *shader) const
{
    for (auto& uniformNameValuePair : shader->mUniformTable)
    {
        GLint uniformLocation = glGetUniformLocation(mProgram, uniformNameValuePair.first.c_str());
        if (uniformLocation == -1)
        {
            FALCON_ENGINE_THROW_EXCEPTION("The location could not be found.");
        }

        uniformNameValuePair.second.mLocation = uniformLocation;
    }
}

}
