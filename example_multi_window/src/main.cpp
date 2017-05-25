#include "ofApp.h"
#include "SecondApp.h"
#include "ofAppGLFWWindow.h"


int main()
{
    ofGLFWWindowSettings settings;

    settings.width = 600;
    settings.height = 600;
    settings.setPosition(glm::vec2(300, 0));
    settings.resizable = true;
    auto mainWindow = ofCreateWindow(settings);

    settings.width = 300;
    settings.height = 300;
    settings.setPosition(glm::vec2(0, 0));
    settings.resizable = false;
    auto secondWindow = ofCreateWindow(settings);

    auto mainApp = std::make_shared<ofApp>();
    auto secondApp = std::make_shared<SecondApp>();

    ofx::RegisterPointerEventsForWindow(mainWindow.get(), mainApp.get());
    ofx::RegisterPointerEventsForWindow(secondWindow.get(), secondApp.get());

    mainApp->secondApp = secondApp;

    ofRunApp(secondWindow, secondApp);
    ofRunApp(mainWindow, mainApp);

    return ofRunMainLoop();
}
