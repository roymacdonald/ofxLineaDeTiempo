//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "ofConstants.h"
#include "ofx/PointerEvents.h"

#if defined(TARGET_OF_IOS)
#include "ofx/PointerEventsiOS.h"
#endif

#if defined(TARGET_OSX)
#include "ofx/PointerEventsMacOS.h"
#endif


#include "ofx/PointerStrokes.h"


/// \brief An alias for easier future core integration.
typedef ofx::PointerEventArgs ofPointerEventArgs;
