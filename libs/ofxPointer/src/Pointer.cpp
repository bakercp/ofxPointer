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


const unsigned long long DefaultGestureEventProcessor::DEFAULT_TAP_DELAY = 500;


DefaultGestureEventProcessor::DefaultGestureEventProcessor():
    _tapThreshold(DEFAULT_TAP_DELAY)
{
    ofx::RegisterPointerEvents(this);
}


DefaultGestureEventProcessor::~DefaultGestureEventProcessor()
{
    ofx::UnregisterPointerEvents(this);
}


bool DefaultGestureEventProcessor::onPointerUp(PointerEvent& evt)
{
    ofLogVerbose("DefaultGestureEventProcessor::onPointerUp") << evt.toString();
    return false;
}


bool DefaultGestureEventProcessor::onPointerDown(PointerEvent& evt)
{
    handlePointerDown(evt);
    ofLogVerbose("DefaultGestureEventProcessor::onPointerDown") << evt.toString();
    return false;
}


bool DefaultGestureEventProcessor::onPointerMove(PointerEvent& evt)
{
    ofLogVerbose("DefaultGestureEventProcessor::onPointerMove") << evt.toString();
    return false;
}


bool DefaultGestureEventProcessor::onPointerCancel(PointerEvent& evt)
{
    ofLogVerbose("DefaultGestureEventProcessor::onPointerCancel") << evt.toString();
    return false;
}


void DefaultGestureEventProcessor::handlePointerDown(const PointerEvent& evt)
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


DefaultPointerEventProcessor::DefaultPointerEventProcessor():
    _consumeMouseEvents(false),
    _consumeTouchEvents(false)
{
    ofAddListener(ofEvents().update, this, &DefaultPointerEventProcessor::update);

    ofAddListener(ofEvents().mouseMoved, this, &DefaultPointerEventProcessor::mouseMoved, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mouseDragged, this, &DefaultPointerEventProcessor::mouseDragged, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mousePressed, this, &DefaultPointerEventProcessor::mousePressed, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mouseReleased, this, &DefaultPointerEventProcessor::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);

    ofAddListener(ofEvents().touchUp, this, &DefaultPointerEventProcessor::touchUp, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchDown, this, &DefaultPointerEventProcessor::touchDown, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchMoved, this, &DefaultPointerEventProcessor::touchMoved, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchDoubleTap, this, &DefaultPointerEventProcessor::touchDoubleTap, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchCancelled, this, &DefaultPointerEventProcessor::touchCancelled, OF_EVENT_ORDER_BEFORE_APP);
}


DefaultPointerEventProcessor::~DefaultPointerEventProcessor()
{
    ofRemoveListener(ofEvents().update, this, &DefaultPointerEventProcessor::update);

    ofRemoveListener(ofEvents().mouseMoved, this, &DefaultPointerEventProcessor::mouseMoved, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().mouseDragged, this, &DefaultPointerEventProcessor::mouseDragged, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().mousePressed, this, &DefaultPointerEventProcessor::mousePressed, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().mouseReleased, this, &DefaultPointerEventProcessor::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);

    ofRemoveListener(ofEvents().touchUp, this, &DefaultPointerEventProcessor::touchUp, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().touchDown, this, &DefaultPointerEventProcessor::touchDown, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().touchMoved, this, &DefaultPointerEventProcessor::touchMoved, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().touchDoubleTap, this, &DefaultPointerEventProcessor::touchDoubleTap, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().touchCancelled, this, &DefaultPointerEventProcessor::touchCancelled, OF_EVENT_ORDER_BEFORE_APP);
}


void DefaultPointerEventProcessor::update(ofEventArgs& evt)
{
}


bool DefaultPointerEventProcessor::mouseMoved(ofMouseEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerMove, p, this);
    return _consumeMouseEvents;
}


bool DefaultPointerEventProcessor::mouseDragged(ofMouseEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerMove, p, this);
    return _consumeMouseEvents;
}


bool DefaultPointerEventProcessor::mousePressed(ofMouseEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerDown, p, this);
    return _consumeMouseEvents;
}


bool DefaultPointerEventProcessor::mouseReleased(ofMouseEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerUp, p, this);
    return _consumeMouseEvents;
}


bool DefaultPointerEventProcessor::touchDown(ofTouchEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerDown, p, this);
    return _consumeTouchEvents;
}


bool DefaultPointerEventProcessor::touchMoved(ofTouchEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerMove, p, this);
    return _consumeTouchEvents;
}


bool DefaultPointerEventProcessor::touchUp(ofTouchEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerUp, p, this);
    return _consumeTouchEvents;
}


bool DefaultPointerEventProcessor::touchDoubleTap(ofTouchEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerGestureEvents().onPointerDoublePress, p, this);
    return _consumeTouchEvents;
}


bool DefaultPointerEventProcessor::touchCancelled(ofTouchEventArgs& e)
{
    PointerEvent p = PointerEvent::toPointerEvent(e);
    ofNotifyEvent(PointerEvents().onPointerCancel, p, this);
    return _consumeTouchEvents;
}


void DefaultPointerEventProcessor::setConsumeMouseEvents(bool consumeMouseEvents)
{
    _consumeMouseEvents = consumeMouseEvents;
}


void DefaultPointerEventProcessor::setConsumeTouchEvents(bool consumeTouchEvents)
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


static std::shared_ptr<AbstractPointerEventProcessor> pPointerEventProcessor = std::shared_ptr<AbstractPointerEventProcessor>(new DefaultPointerEventProcessor());


static std::shared_ptr<AbstractPointerEventProcessor> pPointerGestureProcessor = std::shared_ptr<AbstractPointerEventProcessor>(new DefaultGestureEventProcessor());


void SetPointerEventProcessor(std::shared_ptr<AbstractPointerEventProcessor> processor)
{
    pPointerEventProcessor = processor;
}


void SetPointerGestureProcessor(std::shared_ptr<AbstractPointerEventProcessor> processor)
{
    pPointerGestureProcessor = processor;
}


} // namespace ofx
