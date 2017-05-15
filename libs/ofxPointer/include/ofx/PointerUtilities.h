//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofConstants.h"


namespace ofx {


/// \brief A class for retrieving platform-specific pointer data.
class PointerUtilities
{
public:
    /// \brief Get the system's long press timeout in milliseconds.
    /// \returns the system's long press timeout in milliseconds.
    static uint64_t systemLongPressTimeout();

    /// \brief Get the system's tap timeout in milliseconds.
    /// \returns the system's tap timeout in milliseconds.
    static uint64_t systemTapTimeout();

    OF_DEPRECATED_MSG("Use systemTapTimeout().", static uint64_t getSystemDoubleTapInterval());

    enum
    {
        /// \brief The default long press timeout in milliseconds.
        DEFAULT_LONG_PRESS_TIMEOUT = 500,

        /// \brief The default double tap timeout in milliseconds.
        DEFAULT_TAP_TIMEOUT = 500,

        /// \deprecated
        DEFAULT_DOUBLE_TAP_INTERVAL = DEFAULT_TAP_TIMEOUT

    };


};


} // namespace ofx
