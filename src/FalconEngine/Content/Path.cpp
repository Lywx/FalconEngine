#include <FalconEngine/Content/Path.h>
#include <FalconEngine/Core/Core.h>

#include <boost/filesystem.hpp>

#if BOOST_OS_WINDOWS
#define DIR_SEPARATOR L"\\"
#elif BOOST_OS_LINUX
#define DIR_SEPARATOR L"/"
#endif

namespace fs = boost::filesystem;

namespace FalconEngine {

std::wstring GetCurrentPath()
{
    auto path = fs::current_path().wstring();
    path.append(DIR_SEPARATOR);
    return path;
}

// http://stackoverflow.com/questions/4430780/how-can-i-extract-the-file-name-and-extension-from-a-path-in-c
std::wstring GetFileName(const std::wstring relativePath)
{
    if (Exists(relativePath))
    {
        fs::path file(relativePath);
        return file.filename().wstring();
    }

    return L"";
}

// Return byte number of the given file.
//
// http://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c
std::ifstream::pos_type GetFileSize(const std::wstring relativePath) {
    if (Exists(relativePath))
    {
        std::ifstream file(relativePath, std::ifstream::ate | std::ifstream::binary);
        return file.tellg();
    }

    return std::ifstream::pos_type();
}

bool Exists(const std::wstring relativePath)
{
    return fs::exists(GetCurrentPath() + relativePath);
}

// Return true if successful.
// Return false if there is already a directory named as given or other IO errors happen.
bool CreateDirectory(const std::wstring relativePath)
{
    fs::path path(GetCurrentPath() + relativePath);
    return create_directory(path);
}

}
