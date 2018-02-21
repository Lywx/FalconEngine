#include <FalconEngine/Core/String.h>

#include <algorithm>

using namespace std;

namespace FalconEngine
{

std::string
GetUppercaseString(const std::string& str)
{
    auto uppercase = str;

    for (char& c : uppercase)
    {
        c = char(toupper(c));
    }

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