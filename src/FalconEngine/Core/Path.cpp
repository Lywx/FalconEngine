#include <FalconEngine/Core/Path.h>

#include <boost/filesystem.hpp>

using namespace boost;
using namespace std;

namespace FalconEngine
{

bool
Exist(const string& relativePath)
{
    return filesystem::exists(GetCurrentPath() + relativePath);
}

string
GetCurrentPath()
{
    return filesystem::current_path().string() + FALCON_ENGINE_DIRECTORY_SEPARATOR;
}

string
GetFileDirectory(const string& path)
{
    return filesystem::path(path).parent_path().string() + FALCON_ENGINE_DIRECTORY_SEPARATOR;
}

string
GetFileName(const string& path)
{
    // http://stackoverflow.com/questions/4430780/how-can-i-extract-the-file-name-and-extension-from-a-path-in-c
    return filesystem::path(path).filename().string();
}

std::string GetFileStem(const std::string& path)
{
    return filesystem::path(path).stem().string();
}

string
GetFileExtension(const std::string& path)
{
    // http://stackoverflow.com/questions/959837/how-can-i-know-the-type-of-a-file-using-boost-filesystem
    return filesystem::path(path).extension().string();
}

// ReSharper disable once CppNotAllPathsReturnValue
ifstream::pos_type
GetFileSize(const string& relativePath)
{
    // http://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c
    if (Exist(relativePath))
    {
        ifstream fileStream(relativePath, ifstream::ate | ifstream::binary);
        return fileStream.tellg();
    }

    FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("File not found.");
}

string
ChangeFileExtension(const string& path, const string& extension)
{
    return filesystem::path(path).replace_extension(extension).string();
}

std::string
RemoveFileExtension(const std::string& path)
{
    return filesystem::path(path).replace_extension("").string();
}

// Return true if successful.
// Return false if there is already a directory named as given or other IO errors happen.
bool
CreateDirectory(const string& relativePath)
{
    auto path = GetCurrentPath() + relativePath;
    return filesystem::create_directory(path);
}

}
