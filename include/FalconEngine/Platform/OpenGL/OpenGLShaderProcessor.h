#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Core/GameEngineSettings.h>
#include <FalconEngine/Core/Path.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderSource.h>

namespace FalconEngine
{

class PlatformShaderProcessor
{
public:
    static void
    ProcessShaderIncludeStatement(
        _IN_OUT_ std::string&       shaderSourceString,
        _IN_     const std::string& shaderExtensionLine,
        _IN_     const std::string& shaderPath,
        _IN_OUT_ size_t&            extensionBeginIndex)
    {
        using namespace boost;
        using namespace std;

        static vector<string> shaderExtensionSymbols;
        shaderExtensionSymbols.clear();
        split(shaderExtensionSymbols, shaderExtensionLine, is_any_of(" "));

        if (shaderExtensionSymbols.front() != "#include")
        {
            return;
        }

        auto includeFileName = shaderExtensionSymbols.back();
        trim_if(includeFileName, is_any_of("\""));

        // Search in same directory first.
        auto includeFilePath = GetFileDirectory(shaderPath) + includeFileName;

        // NOTE(Wuxiang): I comment out this because the cmake build system filters out
        // the directory structure during copying shader files into content directory.
        // So that all shader files are in the same directory. No need to do this anymore.
        //
        // Search in shader root directory as last resort.
        if (!GetFileExist(includeFilePath))
        {
            static auto gameEngineSettings = GameEngineSettings::GetInstance();
            if (gameEngineSettings->mShaderDirectory.empty())
            {
                // Do nothing to prevent further exception.
            }
            else
            {
                auto includeFilePathGlobal = gameEngineSettings->mShaderDirectory + includeFileName;
                if (GetFileExist(includeFilePathGlobal))
                {
                    includeFilePath = includeFilePathGlobal;
                }
            }
        }

        auto assetManager = AssetManager::GetInstance();
        auto includeSource = assetManager->LoadShaderSource(includeFilePath);
        shaderSourceString.insert(extensionBeginIndex, includeSource->mSource);
        extensionBeginIndex += includeSource->mSource.size();
    }

    static void
    ProcessShaderExtensionBlock(
        _IN_OUT_ std::string&       shaderSourceString,
        _IN_OUT_ std::string&       shaderExtension,
        _IN_     const std::string& shaderPath,
        _IN_OUT_ size_t&            extensionBeginIndex)
    {
        using namespace boost;
        using namespace std;

        static vector<string> shaderExtensionLines;
        shaderExtensionLines.clear();

        trim(shaderExtension);
        split(shaderExtensionLines, shaderExtension, is_any_of("\n"));
        for (auto& shaderExtensionLine : shaderExtensionLines)
        {
            trim(shaderExtensionLine);
            if (!shaderExtensionLine.empty())
            {
                ProcessShaderIncludeStatement(shaderSourceString, shaderExtensionLine, shaderPath, extensionBeginIndex);
            }
        }
    }

    static void
    ProcessShaderExtension(ShaderSource *shaderSource)
    {
        using namespace std;
        static const string extensionHeaderBeginString = "#fe_extension : enable";
        static const string extensionHeaderEndString = "#fe_extension : disable";

        auto& shaderSourceString = shaderSource->mSource;
        auto extensionHeaderBeginIndex = shaderSourceString.find(extensionHeaderBeginString);
        auto extensionHeaderEndIndex = shaderSourceString.find(extensionHeaderEndString);

        auto extensionHeaderBeginFound = extensionHeaderBeginIndex != string::npos;
        auto extensionHeaderEndFound = extensionHeaderEndIndex != string::npos;

        while (extensionHeaderBeginFound || extensionHeaderEndFound)
        {
            if (extensionHeaderBeginFound && extensionHeaderEndFound
                    && extensionHeaderEndIndex > extensionHeaderBeginIndex)
            {
                auto extensionContentBeginIndex = extensionHeaderBeginIndex + extensionHeaderBeginString.size();
                auto extensionContentEndIndex = extensionHeaderEndIndex - 1;
                string extensionContent = shaderSourceString.substr(extensionContentBeginIndex,
                                          extensionContentEndIndex - extensionContentBeginIndex);

                // Erase the whole extension block remove the original string.
                shaderSourceString.erase(extensionHeaderBeginIndex,
                                         extensionHeaderEndIndex - extensionHeaderBeginIndex
                                         + extensionHeaderEndString.size());

                // Process found extension block.
                ProcessShaderExtensionBlock(shaderSourceString, extensionContent, shaderSource->mFilePath, extensionHeaderBeginIndex);
            }
            else
            {
                FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Extension is not defined correctly.");
            }

            // Try to find next extension block.
            extensionHeaderBeginIndex = shaderSourceString.find(extensionHeaderBeginString);
            extensionHeaderEndIndex = shaderSourceString.find(extensionHeaderEndString);
            extensionHeaderBeginFound = extensionHeaderBeginIndex != string::npos;
            extensionHeaderEndFound = extensionHeaderEndIndex != string::npos;
        }
    }
};

}

#endif