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


#include "ofx/Point.h"


namespace ofx {


Point::Point():
    ofVec3f(0, 0, 0),
    _absolutePosition(0, 0, 0),
    _shape(PointShape()),
    _pressure(0),
    _tangentialPressure(0),
    _rotation(0),
    _tiltX(0),
    _tiltY(0)
{
}


Point::Point(const ofVec3f& position):
    ofVec3f(position),
    _absolutePosition(position),
    _shape(PointShape()),
    _pressure(0),
    _tangentialPressure(0),
    _rotation(0),
    _tiltX(0),
    _tiltY(0)
{
}


Point::Point(const ofVec3f& position, const PointShape& shape):
    ofVec3f(position),
    _absolutePosition(position),
    _shape(shape),
    _pressure(0),
    _tangentialPressure(0),
    _rotation(0),
    _tiltX(0),
    _tiltY(0)
{
}


Point::Point(const ofVec3f& position, float pressure, float tiltX, float tiltY):
    ofVec3f(position),
    _absolutePosition(position),
    _shape(PointShape()),
    _pressure(pressure),
    _tangentialPressure(0),
    _rotation(0),
    _tiltX(tiltX),
    _tiltY(tiltY)
{
}


Point::Point(const ofVec3f& position,
             const ofVec3f& absolutePosition,
             const PointShape& shape,
             float pressure,
             float tangentialPressure,
             float rotation,
             float tiltX,
             float tiltY):
    ofVec3f(position),
    _absolutePosition(absolutePosition),
    _shape(shape),
    _pressure(pressure),
    _tangentialPressure(tangentialPressure),
    _rotation(rotation),
    _tiltX(tiltX),
    _tiltY(tiltY)
{
}


Point::~Point()
{
}


const ofVec3f& Point::getAbsolutePosition() const
{
    return _absolutePosition;
}


float Point::getPressure() const
{
    return _pressure;
}


float Point::getTangentialPressure() const
{
    return _tangentialPressure;
}


float Point::getRotation() const
{
    return _rotation;
}


float Point::getTiltX() const
{
    return _tiltX;
}


float Point::getTiltY() const
{
    return _tiltY;
}


const PointShape& Point::getShape() const
{
    return _shape;
}


} // namespace ofx
