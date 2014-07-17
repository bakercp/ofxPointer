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


#pragma once


#include "ofEvents.h"
#include "PointerEvents.h"


namespace ofx {


class PointerManager
{
public:
    PointerManager();
    virtual ~PointerManager();

	void mouseMoved(ofMouseEventArgs& e);
	void mouseDragged(ofMouseEventArgs& e);
	void mousePressed(ofMouseEventArgs& e);
	void mouseReleased(ofMouseEventArgs& e);

    void touchDown(ofTouchEventArgs& e);
    void touchMoved(ofTouchEventArgs& e);
	void touchUp(ofTouchEventArgs& e);
	void touchDoubleTap(ofTouchEventArgs& e);
	void touchCancelled(ofTouchEventArgs& e);

    template<class ListenerClass>
    void registerAllPointerEvents(ListenerClass* listener);

    template<class ListenerClass>
    void unregisterAllPointerEvents(ListenerClass* listener);

    PointerEvents events;

private:
    // TODO: add pointer history / lookup by id, etc.
};


template<class ListenerClass>
void PointerManager::registerAllPointerEvents(ListenerClass* listener)
{
    ofAddListener(events.onPointerDown, listener, &ListenerClass::onPointerDown);
    ofAddListener(events.onPointerUp, listener, &ListenerClass::onPointerUp);
    ofAddListener(events.onPointerMove, listener, &ListenerClass::onPointerMove);
    ofAddListener(events.onPointerDoubleTap, listener, &ListenerClass::onPointerDoubleTap);
    ofAddListener(events.onPointerCancel, listener, &ListenerClass::onPointerCancel);
}

template<class ListenerClass>
void PointerManager::unregisterAllPointerEvents(ListenerClass* listener)
{
    ofRemoveListener(events.onPointerDown, listener, &ListenerClass::onPointerDown);
    ofRemoveListener(events.onPointerUp, listener, &ListenerClass::onPointerUp);
    ofRemoveListener(events.onPointerMove, listener, &ListenerClass::onPointerMove);
    ofRemoveListener(events.onPointerDoubleTap, listener, &ListenerClass::onPointerDoubleTap);
    ofRemoveListener(events.onPointerCancel, listener, &ListenerClass::onPointerCancel);
}


} // namespace ofx
