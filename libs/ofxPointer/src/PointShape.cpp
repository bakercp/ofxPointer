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


#include "ofx/PointShape.h"


namespace ofx {


PointShape::PointShape():
    _width(0),
    _height(0),
    _ellipseAngle(-1),
    _ellipseMajorAxis(-1),
    _ellipseMinorAxis(-1)
{
}


PointShape::PointShape(float width,
                       float height,
                       float ellipseAngle,
                       float ellipseMajorAxis,
                       float ellipseMinorAxis):
    _width(width),
    _height(height),
    _ellipseAngle(ellipseAngle),
    _ellipseMajorAxis(ellipseMajorAxis),
    _ellipseMinorAxis(ellipseMinorAxis)
{
}


PointShape::~PointShape()
{
}


float PointShape::getWidth() const
{
    return _width;
}


float PointShape::getHeight() const
{
    return _height;
}


float PointShape::getEllipseAngle() const
{
    return _height;
}


float PointShape::getEllipseMajorAxis() const
{
    return _ellipseMajorAxis;
}


float PointShape::getEllipseMinorAxis() const
{
    return _ellipseMinorAxis;
}
    


} // namespace ofx
