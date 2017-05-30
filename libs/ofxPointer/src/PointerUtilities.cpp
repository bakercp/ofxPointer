//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/PointerUtilities.h"
#include "ofUtils.h"


#ifdef TARGET_LINUX
#include <gio/gio.h>
#endif


namespace ofx {



uint64_t PointerUtilities::timestamp()
{
    return ofGetElapsedTimeMillis();
}


#if !defined(TARGET_OSX)


uint64_t PointerUtilities::systemLongPressTimeout()
{
    return DEFAULT_LONG_PRESS_TIMEOUT;
}


uint64_t PointerUtilities::systemTapTimeout()
{
    uint64_t timeMS = 0;
#if defined(TARGET_LINUX)
    GSettings* mouseSettings = g_settings_new("org.gnome.settings-daemon.peripherals.mouse");
    timeMS = g_settings_get_int(mouseSettings, "double-click");
    g_object_unref(mouseSettings);
#elif defined(TARGET_WIN32)
    timeMS = static_cast<uint64_t>(GetDoubleClickTime());
#else
    timeMS = DEFAULT_DOUBLE_TAP_INTERVAL;
#endif
    return timeMS;
}

#endif


uint64_t PointerUtilities::getSystemDoubleTapInterval()
{
    return systemTapTimeout();
}


} // namespace ofx
