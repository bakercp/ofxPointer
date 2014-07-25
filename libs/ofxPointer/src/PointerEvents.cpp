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


static std::shared_ptr<AbstractPointerEventProcessor> pPointerEventProcessor = std::shared_ptr<AbstractPointerEventProcessor>(new DefaultPointerEventProcessor());


void SetPointerEventProcessor(std::shared_ptr<AbstractPointerEventProcessor> processor)
{
    pPointerEventProcessor = processor;
}


DefaultPointerEventProcessor::DefaultPointerEventProcessor()
{
    ofAddListener(ofEvents().mouseMoved, this, &DefaultPointerEventProcessor::mouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &DefaultPointerEventProcessor::mouseDragged);
    ofAddListener(ofEvents().mousePressed, this, &DefaultPointerEventProcessor::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &DefaultPointerEventProcessor::mouseReleased);

    ofAddListener(ofEvents().touchUp, this, &DefaultPointerEventProcessor::touchUp);
    ofAddListener(ofEvents().touchDown, this, &DefaultPointerEventProcessor::touchDown);
    ofAddListener(ofEvents().touchMoved, this, &DefaultPointerEventProcessor::touchMoved);
    ofAddListener(ofEvents().touchCancelled, this, &DefaultPointerEventProcessor::touchCancelled);
}


DefaultPointerEventProcessor::~DefaultPointerEventProcessor()
{
    ofRemoveListener(ofEvents().mouseMoved, this, &DefaultPointerEventProcessor::mouseMoved);
    ofRemoveListener(ofEvents().mouseDragged, this, &DefaultPointerEventProcessor::mouseDragged);
    ofRemoveListener(ofEvents().mousePressed, this, &DefaultPointerEventProcessor::mousePressed);
    ofRemoveListener(ofEvents().mouseReleased, this, &DefaultPointerEventProcessor::mouseReleased);

    ofRemoveListener(ofEvents().touchUp, this, &DefaultPointerEventProcessor::touchUp);
    ofRemoveListener(ofEvents().touchDown, this, &DefaultPointerEventProcessor::touchDown);
    ofRemoveListener(ofEvents().touchMoved, this, &DefaultPointerEventProcessor::touchMoved);
    ofRemoveListener(ofEvents().touchCancelled, this, &DefaultPointerEventProcessor::touchCancelled);
}


void DefaultPointerEventProcessor::mouseMoved(ofMouseEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerMove, p);
}


void DefaultPointerEventProcessor::mouseDragged(ofMouseEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerMove, p);
}


void DefaultPointerEventProcessor::mousePressed(ofMouseEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerDown, p);
}


void DefaultPointerEventProcessor::mouseReleased(ofMouseEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerUp, p);
}


void DefaultPointerEventProcessor::touchDown(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerDown, p);
}


void DefaultPointerEventProcessor::touchMoved(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerMove, p);
}


void DefaultPointerEventProcessor::touchUp(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerUp, p);
}


void DefaultPointerEventProcessor::touchDoubleTap(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);

    PointerEventArgs pTap(p.getPoint(),
                          p.getDeviceID(),
                          p.getPointerID(),
                          p.getType(),
                          p.isPrimary(),
                          p.getButton(),
                          p.getButtons(),
                          p.getModifiers(),
                          2,
                          p.getTimestamp());

    ofNotifyEvent(PointerEvents().onPointerUp, pTap);
}


void DefaultPointerEventProcessor::touchCancelled(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(PointerEvents().onPointerCancel, p);
}

CorePointerEvents& PointerEvents()
{
    static Poco::SingletonHolder<CorePointerEvents> sh;
    return *sh.get();
}


} // namespace ofx
