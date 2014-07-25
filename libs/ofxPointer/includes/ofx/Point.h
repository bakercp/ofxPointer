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


#include "ofVec2f.h"
#include "ofx/PointShape.h"


namespace ofx {


class Point: public ofVec2f
{
public:
    Point();
    Point(const ofVec2f& position);
    Point(const ofVec2f& position, const PointShape& shape);
    Point(const ofVec2f& position, float pressure, float tiltX, float tiltY);
    Point(const ofVec2f& position,
          const PointShape& shape,
          float pressure,
          float tiltX,
          float tiltY);

    /// \brief Destroy the Point.
    virtual ~Point();

    float getPressure() const;

    float getTiltX() const;

    float getTiltY() const;

    const PointShape& getShape() const;

private:
    /// \brief The Point's normalized pressure.
    ///
    /// The normalized pressure is in the range [0, 1].  For devices that do not
    /// support pressure, the value is 0.5 when a button is active or 0
    /// otherwise.
	float _pressure;

    /// \brief The Point's tilt X angle.
    ///
    /// Tilt X is given in degrees [-90, 90] between the Y-Z plane and the plane
    /// containing both the transducer (e.g. pen stylus) axis and the Y axis.  A
    /// positive tilt X is to the right.  The value is 0 if the tilt X is
    /// undefined.
    float _tiltX;

    /// \brief The Point's tilt Y angle.
    ///
    /// Tilt Y is given in degrees [-90, 90] between the X-Z plane and the plane
    /// containing both the transducer (e.g. pen stylus) axis and the X axis.  A
    /// positive tilt Y is toward the user.  The value is 0 if the tilt Y is
    /// undefined.
    float _tiltY;

    /// \brief The Point's shape, if defined.
    PointShape _shape;

};


} // namespace ofx
