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


#include "ofVec3f.h"
#include "ofx/PointShape.h"


namespace ofx {


class Point: public ofVec3f
{
public:
    Point();
    Point(const ofVec3f& position);
    Point(const ofVec3f& position, const PointShape& shape);
    Point(const ofVec3f& position, float pressure, float tiltX, float tiltY);
    Point(const ofVec3f& position,
          const ofVec3f& absolutePosition,
          const PointShape& shape,
          float pressure,
          float tangentialPressure,
          float rotation,
          float tiltX,
          float tiltY);

    /// \brief Destroy the Point.
    virtual ~Point();

    /// \brief Get the position in absolute device coordinates.
    ///
    /// Point extends ofVec3f, providing position relative to the origin of the
    /// screen coordinate system.  Absolute position is returned in absolute
    /// device coordinates, which may be defined at a resolution that differs
    /// from the screen position.
    ///
    /// For devices that do not differentiate between screen and absolute
    /// positions, the value is equal to the screen position.
    ///
    /// \returns the absolute position in device coordinates.
    const ofVec3f& getAbsolutePosition() const;
    

    /// \brief Get the normalized point pressure.
    ///
    /// The normalized pressure is in the range [0, 1].  For devices that do not
    /// support pressure, the value is 0.5 when a button is active or 0
    /// otherwise.
    ///
    /// \returns the normalized point pressure [0, 1].
    float getPressure() const;


    /// \brief Get the Point's normalized tangential pressure.
    ///
    /// The normalized tangential pressure (aka the barrel pressure) is in the
    /// range [0, 1].  For devices that do not support tangential pressure, the
    /// value is 0.
    ///
    /// \returns the normalized tangential pressure [0, 1].
    float getTangentialPressure() const;


    /// \brief Get the Point's rotation in degrees.
    ///
    /// For tablets, the point's rotation is the angle between the "front" of
    /// the transducer (e.g. pen stylus) and the top of the tablet.  For devices
    /// that do not support rotation reporting, the value is 0.
    ///
    /// \note This rotation value similar to but independent of the ellipse
    /// angle value recorded by the PointShape.
    ///
    /// \returns the rotation in degrees.
    float getRotation() const;


    /// \brief Get the Tilt X angle.
    ///
    /// Tilt X is given in degrees [-90, 90] between the Y-Z plane and the plane
    /// containing both the transducer (e.g. pen stylus) axis and the Y axis.  A
    /// positive tilt X is to the right.  The value is 0 if the tilt X is
    /// undefined.
    ///
    /// \returns the Tilt X angle in degrees.
    float getTiltX() const;


    /// \brief Get the Tilt Y angle.
    ///
    /// Tilt Y is given in degrees [-90, 90] between the X-Z plane and the plane
    /// containing both the transducer (e.g. pen stylus) axis and the X axis.  A
    /// positive tilt Y is toward the user.  The value is 0 if the tilt Y is
    /// undefined.
    ///
    /// \returns the Tilt Y angle in degrees.
    float getTiltY() const;


    /// \brief Get the shape of the Point.
    /// \returns The PointShape.
    const PointShape& getShape() const;

private:
    /// \brief The Point's absolute position in device coordinates.
    ofVec3f _absolutePosition;

    /// \brief The Point's normalized pressure.
	float _pressure;

    /// \brief The Point's tangential pressure (aka barrel pressure).
    float _tangentialPressure;

    /// \brief The Point's rotation.
    float _rotation;

    /// \brief The Point tilt X angle.
    float _tiltX;

    /// \brief The Point tilt Y angle.
    float _tiltY;

    /// \brief The Point shape.
    PointShape _shape;

};


} // namespace ofx
