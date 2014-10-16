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


#include "ofx/PointerUtilities.h"

#ifdef TARGET_LINUX
#include <gio/gio.h>
#endif


namespace ofx {


#if !defined(TARGET_OSX)

Poco::Timespan PointerUtilities::getSystemMultiTapInterval()
{
    int timeMS = 0;
#if defined(TARGET_LINUX)
    GSettings* mouseSettings = g_settings_new("org.gnome.settings-daemon.peripherals.mouse");
    timeMS = g_settings_get_int(mouseSettings, "double-click");
    g_object_unref(mouseSettings);
#elif defined(TARGET_WIN32)
    timeMS = GetDoubleClickTime();
#else
    timeMS = DEFAULT_DOUBLE_TAP_INTERVAL;
#endif
    return Poco::Timespan(timeMS * Poco::Timespan::MILLISECONDS);
}

#endif


} // namespace ofx
