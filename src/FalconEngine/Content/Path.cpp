#include <FalconEngine/Content/Path.h>

#include <boost/filesystem.hpp>

#if FALCON_ENGINE_OS_WINDOWS
#define DIR_SEPARATOR "\\"
#elif FALCON_ENGINE_OS_LINUX
#define DIR_SEPARATOR "/"
#endif

using namespace boost;
using namespace std;

namespace FalconEngine
{

wstring
GetWString(string str)
{
    // NOTE(Wuxiang): http://en.cppreference.com/w/cpp/locale/codecvt_utf8_utf16
    // TODO(Wuxiang): Before you starting to work in linux you would not want to change wstring as paramter in IO.
    using CodeOutput = wchar_t;
    using CodeConvert = codecvt_utf8_utf16<CodeOutput>;
    static wstring_convert<CodeConvert> converter;
    return converter.from_bytes(str);
}

bool
Exist(const string relativePath)
{
    return filesystem::exists(GetCurrentPath() + relativePath);
}

string
GetCurrentPath()
{
    return filesystem::current_path().string() + DIR_SEPARATOR;
}

string
GetFileDirectory(const string path)
{
    return filesystem::path(path).parent_path().string() + DIR_SEPARATOR;
}

// http://stackoverflow.com/questions/4430780/how-can-i-extract-the-file-name-and-extension-from-a-path-in-c
string
GetFileName(const string path)
{
    return filesystem::path(path).filename().string();
}

std::string GetFileStem(const std::string path)
{
    return filesystem::path(path).stem().string();
}

string
GetFileExtension(const std::string path)
{
    return filesystem::path(path).extension().string();
}

// Return byte number of the given file.
//
// http://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c
ifstream::pos_type
GetFileSize(const string relativePath)
{
    if (Exist(relativePath))
    {
        ifstream fileStream(relativePath, ifstream::ate | ifstream::binary);
        return fileStream.tellg();
    }

    throw runtime_error("File not found.");
}

string
ChangeFileExtension(const string path, const string extension)
{
    return filesystem::path(path).replace_extension(extension).string();
}

// Return true if successful.
// Return false if there is already a directory named as given or other IO errors happen.
bool CreateDirectory(const string relativePath)
{
    auto path = GetCurrentPath() + relativePath;
    return filesystem::create_directory(path);
}

}
