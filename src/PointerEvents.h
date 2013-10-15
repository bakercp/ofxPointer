// =============================================================================
//
// Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
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
#include "PointerEventArgs.h"


namespace ofx {
namespace Input {

    
// <element onmslostpointercapture = "handler(event)">
class CaptureEvents
{
	ofEvent<PointerEventArgs> gotPointerCapture;
    // Event that is fired when a pointer is captured to the element.

    ofEvent<PointerEventArgs> lostPointerCapture;
    // Event that is triggered when the element loses a pointer capture.
};


class ObjectEvents
{
	ofEvent<PointerEventArgs> 	onPointerHover;
    // Event that is triggered when a contact (normally a pen) moves over an
    // element without touching the surface.

	ofEvent<PointerEventArgs> 	onPointerOut;
    // This event is triggered when a pointer moves from inside to outside the
    // boundaries of this element. This event is always raised, whether or not
    // the pointer is captured to this element.

	ofEvent<PointerEventArgs> 	onPointerOver;
    // Event that is triggered when a contact moves from outside to inside the
    // bounds of this element. This event is always raised, whether or not the
    // pointer is captured to this element.
};


class PointerEvents
{
public:

    ofEvent<PointerEventArgs> 	onPointerDown;
    // Event that is triggered when a contact touches the screen on element.

    ofEvent<PointerEventArgs> 	onPointerUp;
    // Event that is triggered when a contact is raised off of the screen over
    // an element.

	ofEvent<PointerEventArgs> 	onPointerMove;
    // Event that is triggered when a contact moves on the screen while over an
    // element.

    ofEvent<PointerEventArgs> 	onPointerDoubleTap;
    // Event that is triggered when a contact moves on the screen while over an
    // element.


    ofEvent<PointerEventArgs> onPointerCancel;
    //  Fires when the system cancels a pointer event.
    //      This event occurs when the pointer (touch or pen contact) is removed
    //  from the system. Here are common reasons why this might happen:
    //      - A touch contact is canceled by a pen coming into range of the
    //      surface.
    //      - The device doesn't report an active contact for more than 100ms.
    //      - A mapping for a device's monitor changes while contacts are
    //      active. For example, the user changes the position of a screen in a
    //      two screen configuration.
    //      - The desktop is locked or the user logged off.
    //      - The number of simultaneous contacts exceeds the number that the
    //      device can support. For example, if a device supports only two
    //      contact points, if the user has two fingers on a surface, and then
    //      touches it with a third finger, this event is raised.

};


} } // namespace ofx::Input
