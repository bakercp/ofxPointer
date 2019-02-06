//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofBackground(0);
}


void ofApp::draw()
{
}


void ofApp::keyPressed(int key)
{
    switch (key)
    {
        case 'e':
            debugRenderer.setEnabled(!debugRenderer.isEnabled());
        default:
            break;
    }
}

