//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//

#include "ofApp.h"


int main()
{
    ofiOSWindowSettings settings;
    settings.enableRetina = true;
    settings.enableDepth = false;
    settings.enableAntiAliasing = false;
    settings.numOfAntiAliasingSamples = 0;
    settings.enableHardwareOrientation = false;
    settings.enableHardwareOrientationAnimation = false;
    settings.glesVersion = OFXIOS_RENDERER_ES2;
    settings.windowControllerType = ofxiOSWindowControllerType::GL_KIT;
    settings.colorType = ofxiOSRendererColorFormat::RGBA8888;
    settings.depthType = ofxiOSRendererDepthFormat::DEPTH_NONE;
    settings.stencilType = ofxiOSRendererStencilFormat::STENCIL_NONE;
    settings.windowMode = OF_FULLSCREEN;

    settings.enableMultiTouch = true;

    auto mainWindow = ofCreateWindow(settings);
    auto mainApp = std::make_shared<ofApp>();

    ofRunApp(mainWindow, mainApp);

    return ofRunMainLoop();
}
