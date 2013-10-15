// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "PointerManager.h"


namespace ofx {
namespace Input {

    
PointerManager::PointerManager()
{
    ofAddListener(ofEvents().mouseMoved,    this, &PointerManager::mouseMoved);
    ofAddListener(ofEvents().mouseDragged,  this, &PointerManager::mouseDragged);
    ofAddListener(ofEvents().mousePressed,  this, &PointerManager::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &PointerManager::mouseReleased);


    ofAddListener(ofEvents().touchUp,        this, &PointerManager::touchUp);
    ofAddListener(ofEvents().touchDoubleTap, this, &PointerManager::touchDoubleTap);
    ofAddListener(ofEvents().touchDown,      this, &PointerManager::touchDown);
    ofAddListener(ofEvents().touchMoved,     this, &PointerManager::touchMoved);
    ofAddListener(ofEvents().touchCancelled, this, &PointerManager::touchCancelled);
}

PointerManager::~PointerManager()
{
    ofAddListener(ofEvents().mouseMoved,    this, &PointerManager::mouseMoved);
    ofAddListener(ofEvents().mouseDragged,  this, &PointerManager::mouseDragged);
    ofAddListener(ofEvents().mousePressed,  this, &PointerManager::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &PointerManager::mouseReleased);

    ofAddListener(ofEvents().touchUp,        this, &PointerManager::touchUp);
    ofAddListener(ofEvents().touchDoubleTap, this, &PointerManager::touchDoubleTap);
    ofAddListener(ofEvents().touchDown,      this, &PointerManager::touchDown);
    ofAddListener(ofEvents().touchMoved,     this, &PointerManager::touchMoved);
    ofAddListener(ofEvents().touchCancelled, this, &PointerManager::touchCancelled);
}

void PointerManager::mouseMoved(ofMouseEventArgs& e)
{
    PointerEventArgs p(e);
    ofNotifyEvent(events.onPointerMove,p);
    // TODO: register events w/ manager rather than just pass on
}

void PointerManager::mouseDragged(ofMouseEventArgs& e)
{
    PointerEventArgs p(e);
    ofNotifyEvent(events.onPointerMove,p);
    // TODO: register events w/ manager rather than just pass on
}

void PointerManager::mousePressed(ofMouseEventArgs& e)
{
    PointerEventArgs p(e);
    ofNotifyEvent(events.onPointerDown,p);
    // TODO: register events w/ manager rather than just pass on
}

void PointerManager::mouseReleased(ofMouseEventArgs& e)
{
    PointerEventArgs p(e);
    ofNotifyEvent(events.onPointerUp,p);
    // TODO: register events w/ manager rather than just pass on
}

void PointerManager::touchDown(ofTouchEventArgs& e)
{
    PointerEventArgs p(e);
    ofNotifyEvent(events.onPointerDown,p);
    // TODO: register events w/ manager rather than just pass on
}

void PointerManager::touchMoved(ofTouchEventArgs& e)
{
    PointerEventArgs p(e);
    ofNotifyEvent(events.onPointerMove,p);
    // TODO: register events w/ manager rather than just pass on
}

void PointerManager::touchUp(ofTouchEventArgs& e)
{
    PointerEventArgs p(e);
    ofNotifyEvent(events.onPointerUp,p);
    // TODO: register events w/ manager rather than just pass on
}

void PointerManager::touchDoubleTap(ofTouchEventArgs& e)
{
    PointerEventArgs p(e);
    ofNotifyEvent(events.onPointerDoubleTap,p);
    // TODO: register events w/ manager rather than just pass on
}

void PointerManager::touchCancelled(ofTouchEventArgs& e)
{
    PointerEventArgs p(e);
    ofNotifyEvent(events.onPointerCancel,p);
    // TODO: register events w/ manager rather than just pass on
}


} } // namespace ofx::Input
