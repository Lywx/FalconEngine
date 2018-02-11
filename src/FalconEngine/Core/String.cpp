#include <FalconEngine/Core/String.h>

using namespace std;

namespace FalconEngine
{

bool
IsFileExtensionSupported(const string& extension, const vector<string>& extensionSupportedList)
{
    return find(extensionSupportedList.begin(),
                extensionSupportedList.end(),
                extension) != extensionSupportedList.end();
}

}