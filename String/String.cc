//
// String.cc
//

#include <locale>
#include <sstream>
#include <iomanip>

#ifdef __GNUC__

   #include <strings.h>

   // ISO versions of these names
   #define _stricmp strcasecmp

#endif // __GNUC__

#include "String.hh"

bool NoCase::Less(const String &lhs, const String &rhs) noexcept {
   return ::_stricmp(lhs.c_str(), rhs.c_str()) < 0;
} // NoCase::Less(lhs, rhs)

bool NoCase::Equal(const String &lhs, const String &rhs) noexcept {
   return ::_stricmp(lhs.c_str(), rhs.c_str()) == 0;
} // NoCase::Equal(lhs, rhs)

bool NoCase::More(const String &lhs, const String &rhs) noexcept {
   return ::_stricmp(lhs.c_str(), rhs.c_str()) > 0;
} // NoCase::More(lhs, rhs)

template <typename T>
String ToCommas(T number) {
   static std::locale locale("");
   std::stringstream s;
   s.imbue(locale);
   s << std::fixed << number;
   return s.str();
} // ToCommas(number)
