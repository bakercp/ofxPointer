// =============================================================================
//
// Copyright (c) 2009-2014 Christopher Baker <http://christopherbaker.net>
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
#include "Poco/SingletonHolder.h"


namespace ofx {


const unsigned long long GestureEventProcessor::DEFAULT_TAP_DELAY = 500;


GestureEventProcessor::GestureEventProcessor():
    _tapThreshold(DEFAULT_TAP_DELAY)
{
    ofx::RegisterPointerEvents(this);
}


GestureEventProcessor::~GestureEventProcessor()
{
    ofx::UnregisterPointerEvents(this);
}


bool GestureEventProcessor::onPointerUp(PointerEvent& evt)
{
    ofLogVerbose("GestureEventProcessor::onPointerUp") << evt.toString();
    return false;
}


bool GestureEventProcessor::onPointerDown(PointerEvent& evt)
{
    handlePointerDown(evt);
    ofLogVerbose("GestureEventProcessor::onPointerDown") << evt.toString();
    return false;
}


bool GestureEventProcessor::onPointerMove(PointerEvent& evt)
{
    ofLogVerbose("GestureEventProcessor::onPointerMove") << evt.toString();
    return false;
}


bool GestureEventProcessor::onPointerCancel(PointerEvent& evt)
{
    ofLogVerbose("GestureEventProcessor::onPointerCancel") << evt.toString();
    return false;
}


void GestureEventProcessor::handlePointerDown(const PointerEvent& evt)
{
    PointerEvent p(evt);

    PointerDownEventKey key(p.getDeviceID(),
                            p.getPointerID(),
                            p.getButton());

    unsigned long tapCount = 1;

    PointerDownEvents::iterator iter = _pointerDownEvents.find(key);

    if (iter != _pointerDownEvents.end())
    {
        PointerEvent& lastEvent = (*iter).second;

        if (p.getTimestamp() <= (lastEvent.getTimestamp() + _tapThreshold))
        {
//            tapCount += lastEvent.getTapCount();
        }
    }

    p = PointerEvent(p.getEventType(),
                     p.getPoint(),
                     p.getDeviceID(),
                     p.getPointerID(),
                     p.getDeviceType(),
                     p.isPrimary(),
                     p.getButton(),
                     p.getButtons(),
                     p.getModifiers(),
                     p.getTimestamp());

    _pointerDownEvents[key] = p;

    if (2 == tapCount)
    {
        ofNotifyEvent(PointerGestureEvents().onPointerDoublePress, p, this);
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
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerGestureEvents().onPointerDoublePress, p, this);
    return _consumeTouchEvents;
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


GestureEventProcessor& GetGestureEventProcessor()
{
    static Poco::SingletonHolder<GestureEventProcessor> sh;
    return *sh.get();
}


} // namespace ofx
