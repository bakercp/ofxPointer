//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


int main()
{
    ofiOSWindowSettings settings;

    auto window = ofCreateWindow(settings);
    auto mainApp = std::make_shared<ofApp>();
    ofRunApp(window, mainApp);
    return ofRunMainLoop();
}
