#include "ofApp.h"


int main()
{
    ofiOSWindowSettings settings;
    
    // This must be enabled for multiple pointers.
    settings.enableMultiTouch = true;
    
    auto mainWindow = ofCreateWindow(settings);
    auto mainApp = std::make_shared<ofApp>();
    
    ofRunApp(mainWindow, mainApp);

    return ofRunMainLoop();
}
