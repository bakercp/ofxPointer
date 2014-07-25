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


namespace ofx {


class PointShape
{
public:
    PointShape();

    PointShape(float width,
               float height,
               float ellipseAngle = -1,
               float ellipseMajorAxis = -1,
               float ellipseMinorAxis = -1);

    virtual ~PointShape();

    /// \returns the Point width.
    float getWidth() const;

    /// \returns the Point height.
    float getHeight() const;

    /// \returns the Point's ellipse angle in radians or -1 if undefined.
    float getEllipseAngle() const;

    /// \returns the Point's ellipse major axis or -1 if undefined.
    float getEllipseMajorAxis() const;

    /// \returns the Point's ellipse minor axis or -1 if undefined.
    float getEllipseMinorAxis() const;


protected:
    /// \brief Bounding box width.
    float _width;

    /// \brief Bounding box height.
    float _height;

    /// \brief Ellipse angle, if defined.
	float _ellipseAngle;

    /// \brief Ellipse major axis, if defined.
    float _ellipseMajorAxis;

    /// \brief Ellipse minor axis, if defined.
	float _ellipseMinorAxis;

};


} // namespace ofx
