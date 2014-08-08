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


/// \brief A PointShape describes the shape of a pointer.
///
/// For standard pointers, such as a mouse or a pen, the width and height of the
/// PointShape will be set to zero while some touch pointers may define the
/// size of the touch or even an ellipse describing the size and angle of a
/// finger tip.
///
/// When the ellipse is defined, the width and height should describe and axis-
/// aligned bounding box of the ellipse.
class PointShape
{
public:
    /// \brief Create a default PointShape.
    PointShape();

    /// \brief Create a PointShape with parameters.
    PointShape(float width,
               float height,
               float ellipseMajorAxis = 0,
               float ellipseMinorAxis = 0,
               float ellipseAngle = 0);

    /// \brief Destroy the PointShape.
    virtual ~PointShape();

    /// \brief Get the width of the PointShape.
    ///
    /// When an ellipse is defined, this represents the width of the ellipse's
    /// axis-aligned bounding box.
    ///
    /// \returns the Point width.
    float getWidth() const;

    /// \brief Get the height of the PointShape.
    ///
    /// When an ellipse is defined, this represents the height of the ellipse's
    /// axis-aligned bounding box.
    ///
    /// \returns the Point height.
    float getHeight() const;

    /// \brief Get the angle of the PointShape ellipse.
    ///
    /// Some touch pointers may define the elliptical shape and angle of a
    /// contact point.
    ///
    /// \returns the Point's ellipse angle in degrees.
    float getEllipseAngle() const;

    /// \brief Get the major axis of the PointShape ellipse.
    ///
    /// Some touch pointers may define the elliptical shape and angle of a
    /// contact point.
    ///
    /// \returns the Point's ellipse major axis.
    float getEllipseMajorAxis() const;

    /// \brief Get the minor axis of the PointShape ellipse.
    ///
    /// Some touch pointers may define the elliptical shape and angle of a
    /// contact point.
    ///
    /// \returns the Point's ellipse minor axis.
    float getEllipseMinorAxis() const;

protected:
    /// \brief Bounding box width.
    float _width;

    /// \brief Bounding box height.
    float _height;

    /// \brief Ellipse major axis.
    float _ellipseMajorAxis;

    /// \brief Ellipse minor axis.
	float _ellipseMinorAxis;

    /// \brief Ellipse angle in degrees.
	float _ellipseAngle;

};


} // namespace ofx
