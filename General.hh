//
// General.hh
//

#ifndef General_hh
#define General_hh

#include <cstddef> // For size_t

// for (ever)
#define ever ;;

// The opposite of explicit
#define implicit

// This is used to mark virtual base functions as pure.
// This is easier to isolate in a global search than what C++ specifies.
#define pure = 0

// Allow virtual functions to be documented as either initial or subsequent.
// Note C++11 uses "override" as a trailing specifier - this is up front.
// Unfortunately, it isn't checked by the compiler...
#define hook      virtual
#define overrides virtual

typedef unsigned char  byte;
typedef unsigned short word;

typedef char    ascii;
typedef wchar_t unicode;

typedef size_t Pos;
typedef size_t Size;
typedef unsigned Length;

class _General_ {
}; // _General_

class _Template_ : private _General_ {
}; // _Template_

#endif // General_hh
