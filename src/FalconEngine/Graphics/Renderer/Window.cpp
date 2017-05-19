#include <FalconEngine/Graphics/Renderer/Window.h>

namespace FalconEngine
{
/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Window::Window() :
    mWidth(),
    mHeight(),
    mNear(),
    mFar()
{
}

Window::Window(int width, int height, float near, float far) :
    mWidth(width),
    mHeight(height),
    mNear(near),
    mFar(far)
{
}

}
