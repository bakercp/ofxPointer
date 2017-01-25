//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <cstdint>


namespace ofx {


/// \brief A class for retrieving platform-specific pointer data.
class PointerUtilities
{
public:
    /// \brief Get the system's double tap interval in milliseconds.
    /// \returns the system's double tap interval in milliseconds.
    static uint64_t getSystemDoubleTapInterval();

    enum
    {
        /// \brief The default double tap interval in milliseconds.
        DEFAULT_DOUBLE_TAP_INTERVAL = 500
    };

};


} // namespace ofx
