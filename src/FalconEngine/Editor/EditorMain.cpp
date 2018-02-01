#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_WINDOW_QT)
#include <QtWidgets/QApplication>
#include <FalconEngine/Platform/Qt/QtGameEngineWindow.h>

using namespace FalconEngine;

int
main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationDomain("OrgDomain");
    QCoreApplication::setOrganizationName("OrgName");
    QCoreApplication::setApplicationName("AppName");
    QCoreApplication::setApplicationVersion("1.0.0");

    PlatformGameEngineWindow window;
    window.show();
    return app.exec();
}

#endif