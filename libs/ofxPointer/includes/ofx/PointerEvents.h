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


#pragma once


#include <map>
#include "ofEvents.h"
#include "ofTypes.h"
#include "PointerEventArgs.h"


namespace ofx {


class AbstractPointerEventProcessor
{
public:
    virtual ~AbstractPointerEventProcessor()
    {
    }

};


void SetPointerEventProcessor(std::shared_ptr<AbstractPointerEventProcessor> processor);


class DefaultPointerEventProcessor: public AbstractPointerEventProcessor
{
public:
    DefaultPointerEventProcessor();
    virtual ~DefaultPointerEventProcessor();

	void mouseMoved(ofMouseEventArgs& e);
	void mouseDragged(ofMouseEventArgs& e);
	void mousePressed(ofMouseEventArgs& e);
	void mouseReleased(ofMouseEventArgs& e);

    void touchDown(ofTouchEventArgs& e);
    void touchMoved(ofTouchEventArgs& e);
	void touchUp(ofTouchEventArgs& e);
	void touchDoubleTap(ofTouchEventArgs& e);
	void touchCancelled(ofTouchEventArgs& e);

//private:
//    std::map<std::pair<long, unsigned long>, std::pair<unsigned long, Poco::Timestamp> > _clickHistory;
//    std::map<std::pair<long, unsigned long>, std::pair<unsigned long, Poco::Timestamp> > _tapHistory;
//
//    /// \brief Record a mouse click.
//    /// \param id The mouse id.
//    /// \param id The button id.
//    /// \returns The number of clicks recorded for this mouse button.
//    unsigned long click(long id, unsigned long);
//
//    /// \brief Record a touch tap click.
//    /// \param id The mouse id.
//    /// \param id The button id.
//    /// \returns The number of taps recorded for this touch.
//    unsigned long tap(long id, unsigned long);
//
//    enum
//    {
//        DEFAULT_TAP_THRESHOLD = 500
//    };
//
};


class CorePointerEvents
{
public:
    /// \brief Event that is triggered when a point is introduced.
    ofEvent<PointerEventArgs> onPointerDown;

    /// \brief Event that is triggered when a point is removed.
    ofEvent<PointerEventArgs> onPointerUp;

    /// \brief Event that is triggered when a point moves.
	ofEvent<PointerEventArgs> onPointerMove;

    ///  \brief Event when the system cancels a pointer event.
    ///
    /// This event occurs when the pointer (touch or pen contact) is removed
    /// from the system. Here are common reasons why this might happen:
    ///     - A touch contact is canceled by a pen coming into range of the
    ///     surface.
    ///     - The device doesn't report an active contact for more than 100ms.
    ///     - A mapping for a device's monitor changes while contacts are
    ///     active. For example, the user changes the position of a screen in a
    ///     two screen configuration.
    ///     - The desktop is locked or the user logged off.
    ///     - The number of simultaneous contacts exceeds the number that the
    ///     device can support. For example, if a device supports only two
    ///     contact points, if the user has two fingers on a surface, and then
    ///     touches it with a third finger, this event is raised.
    ofEvent<PointerEventArgs> onPointerCancel;

};


CorePointerEvents& PointerEvents();


template<class ListenerClass>
void RegisterPointerEvents(ListenerClass* listener,
                           int prio = OF_EVENT_ORDER_AFTER_APP)
{
    ofAddListener(PointerEvents().onPointerDown, listener, &ListenerClass::onPointerDown, prio);
    ofAddListener(PointerEvents().onPointerUp, listener, &ListenerClass::onPointerUp, prio);
    ofAddListener(PointerEvents().onPointerMove, listener, &ListenerClass::onPointerMove, prio);
    ofAddListener(PointerEvents().onPointerCancel, listener, &ListenerClass::onPointerCancel, prio);
}


template<class ListenerClass>
void UnregisterPointerEvents(ListenerClass* listener)
{
    ofRemoveListener(PointerEvents().onPointerDown, listener, &ListenerClass::onPointerDown);
    ofRemoveListener(PointerEvents().onPointerUp, listener, &ListenerClass::onPointerUp);
    ofRemoveListener(PointerEvents().onPointerMove, listener, &ListenerClass::onPointerMove);
    ofRemoveListener(PointerEvents().onPointerCancel, listener, &ListenerClass::onPointerCancel);
}


} // namespace ofx
