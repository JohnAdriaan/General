//
// String.hh
//

#ifndef String_hh
#define String_hh

#include <string>

typedef std::string String;

inline int ToNumber(const String &string) {
   return ::atoi(string.c_str());
} // ToNumber(String)

template <typename T>
inline String ToString(T number) {
   return std::to_string(number);
} // ToString(number)

template <typename T>
String ToCommas(T number);

template <typename T>
inline String &operator +=(String &lhs, T number) {
   return lhs += ToString(number);
} // operator +=(String, number)

// For case-insensitive comparisons in the STL. e.g.:
//    typedef std::set<String, NoCase> Set;
//    typedef std::map<String, Set, NoCase> MapSet;
//    typedef std::map<String, String, NoCase> Map;
struct NoCase {

   inline bool operator()(const String &lhs, const String &rhs) const noexcept;

   static bool Less (const String &lhs, const String &rhs) noexcept;
   static bool Equal(const String &lhs, const String &rhs) noexcept;
   static bool More (const String &lhs, const String &rhs) noexcept;

}; // NoCase

inline bool NoCase::operator()(const String &lhs, const String &rhs) const noexcept {
   return Less(lhs, rhs);
} // NoCase::operator()(lhs, rhs)

#endif // String_hh
