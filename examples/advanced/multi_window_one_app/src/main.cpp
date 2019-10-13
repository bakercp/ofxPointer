//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"
#include "ofAppGLFWWindow.h"


int main()
{
    ofGLFWWindowSettings settings;

    settings.setSize(600, 600);
    settings.setPosition(glm::vec2(300, 0));
    settings.resizable = true;
    auto mainWindow = ofCreateWindow(settings);
    mainWindow->setWindowTitle("Main Window");

    settings.setSize(300, 300);
    settings.setPosition(glm::vec2(0, 0));
    settings.resizable = false;
    auto secondWindow = ofCreateWindow(settings);
    secondWindow->setVerticalSync(false);
    secondWindow->setWindowTitle("Second Window");

    auto mainApp = std::make_shared<ofApp>();

    // Register pointer events for both windows.
    ofx::RegisterPointerEventForWindow(mainWindow.get(), mainApp.get());
    ofx::RegisterPointerEventForWindow(secondWindow.get(), mainApp.get());

    // Set up renderers for each window.
    ofx::PointerDebugRenderer::Settings debugSettings;

    // Set render settings for main window.
    mainApp.get()->renderers[mainWindow.get()].setup(debugSettings);

    // Set render settings for second window.
    debugSettings.rendererSettings.minimumStrokeWidth = 25;
    debugSettings.rendererSettings.maximumStrokeWidth = 50;

    mainApp.get()->renderers[secondWindow.get()].setup(debugSettings);

    // Connect windows.
    ofAddListener(secondWindow->events().draw,
                  mainApp.get(),
                  &ofApp::drawSecondWindow);

    ofRunApp(mainWindow, mainApp);

    return ofRunMainLoop();

}
