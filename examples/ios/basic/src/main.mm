//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//

#include "ofApp.h"


int main()
{
    ofiOSWindowSettings settings;
    settings.enableMultiTouch = true;

    auto mainWindow = ofCreateWindow(settings);
    auto mainApp = std::make_shared<ofApp>();

    ofRunApp(mainWindow, mainApp);

    return ofRunMainLoop();
}
