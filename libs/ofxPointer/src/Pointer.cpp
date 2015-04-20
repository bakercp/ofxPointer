// =============================================================================
//
// Copyright (c) 2009-2015 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/Pointer.h"
#include "ofx/PointerUtilities.h"
#include "Poco/SingletonHolder.h"


namespace ofx {


PointerGestureEventProcessor::PointerGestureEventProcessor()
{
    RegisterPointerEvents(this, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().update, this, &PointerGestureEventProcessor::update);
}


PointerGestureEventProcessor::~PointerGestureEventProcessor()
{
    ofRemoveListener(ofEvents().update, this, &PointerGestureEventProcessor::update);
    UnregisterPointerEvents(this);
}


void PointerGestureEventProcessor::update(ofEventArgs& evt)
{
}


bool PointerGestureEventProcessor::onPointerUp(PointerEvent& evt)
{
    return false;
}


bool PointerGestureEventProcessor::onPointerDown(PointerEvent& evt)
{
    handlePointerDown(evt);
    return false;
}


bool PointerGestureEventProcessor::onPointerMove(PointerEvent& evt)
{
    return false;
}


bool PointerGestureEventProcessor::onPointerCancel(PointerEvent& evt)
{
    return false;
}


void PointerGestureEventProcessor::handlePointerDown(PointerEvent& evt)
{
    PointerEvent::PointerID id(evt.getDeviceID(),
                               evt.getPointerID());

    PointerPressEventKey key(id, evt.getButton());

    handleMultiPress(evt);

    _pointerDownEvents[key] = evt;

}


void PointerGestureEventProcessor::handlePointerUp(PointerEvent& evt)
{
    PointerEvent::PointerID id(evt.getDeviceID(),
                               evt.getPointerID());

    PointerPressEventKey key(id, evt.getButton());

    _pointerUpEvents[key] = evt;
}


void PointerGestureEventProcessor::handlePointerMove(PointerEvent& evt)
{
}


void PointerGestureEventProcessor::handlePointerCancel(PointerEvent& evt)
{
}


void PointerGestureEventProcessor::handleMultiPress(PointerEvent& evt)
{
    PointerEvent::PointerID id(evt.getDeviceID(),
                               evt.getPointerID());

    PointerPressEventKey key(id, evt.getButton());

    Poco::Timespan _doublePressThreshold = PointerUtilities::getSystemDoublePressInterval();

    PointerPressEvents::iterator iter = _pointerDownEvents.find(key);

    if (iter != _pointerDownEvents.end())
    {
        PointerEvent& lastEvent = (*iter).second;

        if (evt.getTimestamp() <= (lastEvent.getTimestamp() + _doublePressThreshold.totalMilliseconds()))
        {
            evt._pressCount = lastEvent.getPressCount() + 1;
        }

        if (2 == evt.getPressCount())
        {
            ofNotifyEvent(PointerGestureEvents().onPointerDoublePress, evt, this);
        }
    }
}


PointerEventProcessor::PointerEventProcessor():
    _consumeMouseEvents(false),
    _consumeTouchEvents(false)
{
    ofAddListener(ofEvents().update, this, &PointerEventProcessor::update);

    ofAddListener(ofEvents().mouseMoved, this, &PointerEventProcessor::mouseMoved, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mouseDragged, this, &PointerEventProcessor::mouseDragged, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mousePressed, this, &PointerEventProcessor::mousePressed, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mouseReleased, this, &PointerEventProcessor::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);

    ofAddListener(ofEvents().touchUp, this, &PointerEventProcessor::touchUp, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchDown, this, &PointerEventProcessor::touchDown, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchMoved, this, &PointerEventProcessor::touchMoved, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchDoubleTap, this, &PointerEventProcessor::touchDoubleTap, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchCancelled, this, &PointerEventProcessor::touchCancelled, OF_EVENT_ORDER_BEFORE_APP);
}


PointerEventProcessor::~PointerEventProcessor()
{
    ofRemoveListener(ofEvents().update, this, &PointerEventProcessor::update);

    ofRemoveListener(ofEvents().mouseMoved, this, &PointerEventProcessor::mouseMoved, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().mouseDragged, this, &PointerEventProcessor::mouseDragged, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().mousePressed, this, &PointerEventProcessor::mousePressed, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().mouseReleased, this, &PointerEventProcessor::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);

    ofRemoveListener(ofEvents().touchUp, this, &PointerEventProcessor::touchUp, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().touchDown, this, &PointerEventProcessor::touchDown, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().touchMoved, this, &PointerEventProcessor::touchMoved, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().touchDoubleTap, this, &PointerEventProcessor::touchDoubleTap, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().touchCancelled, this, &PointerEventProcessor::touchCancelled, OF_EVENT_ORDER_BEFORE_APP);
}


void PointerEventProcessor::update(ofEventArgs& evt)
{
}


bool PointerEventProcessor::mouseMoved(ofMouseEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerMove, p, this);
    return _consumeMouseEvents;
}


bool PointerEventProcessor::mouseDragged(ofMouseEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerMove, p, this);
    return _consumeMouseEvents;
}


bool PointerEventProcessor::mousePressed(ofMouseEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerDown, p, this);
    return _consumeMouseEvents;
}


bool PointerEventProcessor::mouseReleased(ofMouseEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerUp, p, this);
    return _consumeMouseEvents;
}


bool PointerEventProcessor::touchDown(ofTouchEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerDown, p, this);
    return _consumeTouchEvents;
}


bool PointerEventProcessor::touchMoved(ofTouchEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerMove, p, this);
    return _consumeTouchEvents;
}


bool PointerEventProcessor::touchUp(ofTouchEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerUp, p, this);
    return _consumeTouchEvents;
}


bool PointerEventProcessor::touchDoubleTap(ofTouchEventArgs& e)
{
    // We do not pass on these events.
    // We consume it and let the gesture handler keep track of them.
    return true;
}


bool PointerEventProcessor::touchCancelled(ofTouchEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerCancel, p, this);
    return _consumeTouchEvents;
}


void PointerEventProcessor::setConsumeMouseEvents(bool consumeMouseEvents)
{
    _consumeMouseEvents = consumeMouseEvents;
}


void PointerEventProcessor::setConsumeTouchEvents(bool consumeTouchEvents)
{
    _consumeTouchEvents = consumeTouchEvents;
}


CorePointerEvents& PointerEvents()
{
    static Poco::SingletonHolder<CorePointerEvents> sh;
    return *sh.get();
}


CorePointerGestureEvents& PointerGestureEvents()
{
    static Poco::SingletonHolder<CorePointerGestureEvents> sh;
    return *sh.get();
}


PointerEventProcessor& GetPointerEventProcessor()
{
    static Poco::SingletonHolder<PointerEventProcessor> sh;
    return *sh.get();
}


PointerGestureEventProcessor& GetPointerGestureEventProcessor()
{
    static Poco::SingletonHolder<PointerGestureEventProcessor> sh;
    return *sh.get();
}


} // namespace ofx
