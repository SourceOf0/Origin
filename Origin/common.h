#ifndef INCLUDED_COMMON_H
#define INCLUDED_COMMON_H

#include "resource.h"
#include <stdio.h>

#ifdef _DEBUG
#   define debugPrint( str, ... ) \
      { \
        char c[256]; \
        sprintf_s( c, 256, str, __VA_ARGS__ ); \
        OutputDebugString( c ); \
      }
#else
#    define debugPrint( str, ... ) // ‹óŽÀ‘•
#endif // _DEBUG

#endif // INCLUDED_COMMON_H