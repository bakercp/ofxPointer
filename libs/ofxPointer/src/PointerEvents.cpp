// =============================================================================
//
// Copyright (c) 2010-2014 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/PointerEvents.h"
#include "ofx/PointerUtilities.h"
#include "Poco/SingletonHolder.h"
#include "ofConstants.h"
#include "ofLog.h"


namespace ofx {



DefaultPointerEventProcessor::DefaultPointerEventProcessor():
    _multiTapInterval(PointerUtilities::getSystemMultiTapInterval()),
    _consumeMouseEvents(true),
    _consumeTouchEvents(true)
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

    std::cout << "Total MS: " << _multiTapInterval.totalMilliseconds() << endl;
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
    // updating.
}


bool DefaultPointerEventProcessor::mouseMoved(ofMouseEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerMove, p, this);
    return _consumeMouseEvents;
}


bool DefaultPointerEventProcessor::mouseDragged(ofMouseEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerMove, p, this);
    return _consumeMouseEvents;
}


bool DefaultPointerEventProcessor::mousePressed(ofMouseEventArgs& e)
{
    handlePointerDown(PointerEventArgs::toPointerEventArgs(e));
    return _consumeMouseEvents;
}


bool DefaultPointerEventProcessor::mouseReleased(ofMouseEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerUp, p, this);
    return _consumeMouseEvents;
}


bool DefaultPointerEventProcessor::touchDown(ofTouchEventArgs& e)
{
    handlePointerDown(PointerEventArgs::toPointerEventArgs(e));
    return _consumeTouchEvents;
}


bool DefaultPointerEventProcessor::touchMoved(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerMove, p, this);
    return _consumeTouchEvents;
}


bool DefaultPointerEventProcessor::touchUp(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerUp, p, this);
    return _consumeTouchEvents;
}


bool DefaultPointerEventProcessor::touchDoubleTap(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerGestureEvents().onPointerDoublePress, p, this);
    return _consumeTouchEvents;
}


bool DefaultPointerEventProcessor::touchCancelled(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
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


void DefaultPointerEventProcessor::handlePointerDown(const PointerEventArgs& evt)
{
    PointerEventArgs p(evt);

    PointerDownEventArgsKey key(p.getDeviceID(),
                                p.getPointerID(),
                                p.getButton());

    unsigned long tapCount = 1;

    PointerDownEvents::iterator iter = _pointerDownEvents.find(key);

    if (iter != _pointerDownEvents.end())
    {
        PointerEventArgs& lastEvent = (*iter).second;

        if (p.getTimestamp() <= (lastEvent.getTimestamp() + _multiTapInterval.totalMicroseconds()))
        {
            tapCount += lastEvent.getTapCount();
        }
    }

    p = PointerEventArgs(p.getEventType(),
                         p.getPoint(),
                         p.getDeviceID(),
                         p.getPointerID(),
                         p.getDeviceType(),
                         p.isPrimary(),
                         p.getButton(),
                         p.getButtons(),
                         p.getModifiers(),
                         tapCount,
                         p.getTimestamp());

    _pointerDownEvents[key] = p;

    ofNotifyEvent(PointerEvents().onPointerDown, p, this);
    
    if (2 == tapCount)
    {
        ofNotifyEvent(PointerGestureEvents().onPointerDoublePress, p, this);
    }
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


void SetPointerEventProcessor(std::shared_ptr<AbstractPointerEventProcessor> processor)
{
    pPointerEventProcessor = processor;
}


} // namespace ofx
