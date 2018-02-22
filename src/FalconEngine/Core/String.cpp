#include <FalconEngine/Core/String.h>

#include <algorithm>

using namespace std;

namespace FalconEngine
{

std::string
GetUppercaseString(const std::string& str)
{
    auto uppercase = str;

    std::transform(str.begin(), str.end(), uppercase.begin(), ::toupper);

    return uppercase;
}

bool
IsFileExtensionSupported(const string& extension, const vector<string>& extensionSupportedList)
{
    return find(extensionSupportedList.begin(),
                extensionSupportedList.end(),
                extension) != extensionSupportedList.end();
}

}