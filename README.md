# ofxPointer

## Description

This frameworks adapts the [W3C Pointer Event](http://www.w3.org/TR/pointerevents/) specification to work with openFrameworks.

## Features

Currently the openFrameworks pointer model separates touch and mouse events, making cross platform development a little tricky.

Simply put, `ofxPointer` merges pointer, touch and pen input into a single extensible interface.

A typical program will now look like this:


```c++

#pragma once


#include "ofMain.h"
#include "ofxPointer.h"


class ofApp: public ofBaseApp
{
public:
    void setup() override
    {
        // Register the pointer events.
        ofx::RegisterPointerEvents(this);
    }

    void update() override
    {
        // Update
    }


    void draw() override
    {
        // Draw
    }


    void onPointerUp(ofx::PointerEventArgs& evt)
    {
        ofLogNotice("ofApp::onPointerUp") << evt;
    }


    void onPointerDown(ofx::PointerEventArgs& evt)
    {
        ofLogNotice("ofApp::onPointerDown") << evt;
    }


    void pointerMove(ofx::PointerEventArgs& evt)
    {
        ofLogNotice("ofApp::onPointerMove") << evt;
    }


    void onPointerCancel(ofx::PointerEventArgs& evt)
    {
        ofLogNotice("ofApp::onPointerCancel") << evt;
    }

};

```

For iOS compatibility, see see the simple and advanced iOS examples.


## Getting Started

To get started, generate the example project files using the openFrameworks [Project Generator](http://openframeworks.cc/learning/01_basics/how_to_add_addon_to_project/).

## Documentation

API documentation can be found here.

## Build Status

Linux, macOS [![Build Status](https://travis-ci.org/bakercp/ofxPointer.svg?branch=master)](https://travis-ci.org/bakercp/ofxPointer)

Visual Studio, MSYS [![Build status](https://ci.appveyor.com/api/projects/status/p2v0cy2yy8gli402/branch/master?svg=true)](https://ci.appveyor.com/project/bakercp/ofxpointer/branch/master)


## Compatibility

The `stable` branch of this repository is meant to be compatible with the openFrameworks [stable branch](https://github.com/openframeworks/openFrameworks/tree/stable), which corresponds to the latest official openFrameworks release.

The `master` branch of this repository is meant to be compatible with the openFrameworks [master branch](https://github.com/openframeworks/openFrameworks/tree/master).

Some past openFrameworks releases are supported via tagged versions, but only `stable` and `master` branches are actively supported.

## Versioning

This project uses Semantic Versioning, although strict adherence will only come into effect at version 1.0.0.

## Licensing

See `LICENSE.md`.

## Contributing

Pull Requests are always welcome, so if you make any improvements please feel free to float them back upstream :)

1. Fork this repository.
2. Create your feature branch (`git checkout -b my-new-feature`).
3. Commit your changes (`git commit -am 'Add some feature'`).
4. Push to the branch (`git push origin my-new-feature`).
5. Create new Pull Request.
