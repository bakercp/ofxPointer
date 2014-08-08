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


#include "PointerEvents.h"
#include "Poco/SingletonHolder.h"


namespace ofx {

const Poco::Timespan DefaultPointerEventProcessor::DEFAULT_TAP_DELAY = Poco::Timespan::MILLISECONDS * 500;


DefaultPointerEventProcessor::DefaultPointerEventProcessor():
    _tapThreshold(DEFAULT_TAP_DELAY)
{
    ofAddListener(ofEvents().update, this, &DefaultPointerEventProcessor::update);

    ofAddListener(ofEvents().mouseMoved, this, &DefaultPointerEventProcessor::mouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &DefaultPointerEventProcessor::mouseDragged);
    ofAddListener(ofEvents().mousePressed, this, &DefaultPointerEventProcessor::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &DefaultPointerEventProcessor::mouseReleased);

    ofAddListener(ofEvents().touchUp, this, &DefaultPointerEventProcessor::touchUp);
    ofAddListener(ofEvents().touchDown, this, &DefaultPointerEventProcessor::touchDown);
    ofAddListener(ofEvents().touchMoved, this, &DefaultPointerEventProcessor::touchMoved);
    ofAddListener(ofEvents().touchDoubleTap, this, &DefaultPointerEventProcessor::touchDoubleTap);
    ofAddListener(ofEvents().touchCancelled, this, &DefaultPointerEventProcessor::touchCancelled);
}


DefaultPointerEventProcessor::~DefaultPointerEventProcessor()
{
    ofRemoveListener(ofEvents().update, this, &DefaultPointerEventProcessor::update);

    ofRemoveListener(ofEvents().mouseMoved, this, &DefaultPointerEventProcessor::mouseMoved);
    ofRemoveListener(ofEvents().mouseDragged, this, &DefaultPointerEventProcessor::mouseDragged);
    ofRemoveListener(ofEvents().mousePressed, this, &DefaultPointerEventProcessor::mousePressed);
    ofRemoveListener(ofEvents().mouseReleased, this, &DefaultPointerEventProcessor::mouseReleased);

    ofRemoveListener(ofEvents().touchUp, this, &DefaultPointerEventProcessor::touchUp);
    ofRemoveListener(ofEvents().touchDown, this, &DefaultPointerEventProcessor::touchDown);
    ofRemoveListener(ofEvents().touchMoved, this, &DefaultPointerEventProcessor::touchMoved);
    ofRemoveListener(ofEvents().touchDoubleTap, this, &DefaultPointerEventProcessor::touchDoubleTap);
    ofRemoveListener(ofEvents().touchCancelled, this, &DefaultPointerEventProcessor::touchCancelled);
}


void DefaultPointerEventProcessor::update(ofEventArgs& evt)
{
    // updating.
}


void DefaultPointerEventProcessor::mouseMoved(ofMouseEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerMove, p, this);
}


void DefaultPointerEventProcessor::mouseDragged(ofMouseEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerMove, p, this);
}


void DefaultPointerEventProcessor::mousePressed(ofMouseEventArgs& e)
{
    handlePointerDown(PointerEventArgs::toPointerEventArgs(e));
}


void DefaultPointerEventProcessor::mouseReleased(ofMouseEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerUp, p, this);
}


void DefaultPointerEventProcessor::touchDown(ofTouchEventArgs& e)
{
    handlePointerDown(PointerEventArgs::toPointerEventArgs(e));
}


void DefaultPointerEventProcessor::touchMoved(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerMove, p, this);
}


void DefaultPointerEventProcessor::touchUp(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerUp, p, this);
}


void DefaultPointerEventProcessor::touchDoubleTap(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerGestureEvents().onPointerDoublePress, p, this);
}


void DefaultPointerEventProcessor::touchCancelled(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerCancel, p, this);
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

        if (p.getTimestamp() <= (lastEvent.getTimestamp() + _tapThreshold.totalMicroseconds()))
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
